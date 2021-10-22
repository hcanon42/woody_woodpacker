# include "../includes/packer.h"

int		initialize_packer(t_packer *pack, char *file_to_open)
{
	int		bytes_read;

	pack->_type = 1;
	openFile(file_to_open, pack);
	if (pack->_type == 0 || pack->_size <= 130)
		return (-1);
	if (!(pack->_content = (char *)malloc(sizeof(char) * pack->_size)))
	{
		close(pack->_fd);
		return (-1);
	}
	bytes_read = read(pack->_fd, pack->_content, pack->_size);
	if (bytes_read == -1 || pack->_content[0] != (char)127 || pack->_content[1] != 'E'
	|| pack->_content[2] != 'L' || pack->_content[3] != 'F' || pack->_content[4] != 2)
	{
		ft_putstr_fd("Error: Wrong File Type\n", 2);
		return (-1);
	}
	return (0);
}

void	openFile(char *to_read, t_packer *pack)
{
	pack->_fd = open(to_read, O_RDONLY);
	if (pack->_fd == -1)
	{
		pack->_type = 0;
		return ;
	}
	pack->_size = lseek(pack->_fd, 0, SEEK_END);
	lseek(pack->_fd, 0, SEEK_SET);
}

void insert_code(unsigned char *ptr)
{
	/* On insert l'instruction pusha avant notre shellcode */
	ft_memcpy(ptr, pusha, ft_strlen(pusha) - 1);
	ptr += ft_strlen(pusha) - 1;

	/* On copie notre shellcode */
	ft_memcpy(ptr, shellcode, ft_strlen(shellcode) - 1);
	ptr += ft_strlen(shellcode) - 1;

	/* On place l'instruction popa juste avant notre JMP */
	ft_memcpy(ptr, popa, ft_strlen(popa) - 1);
	ptr += ft_strlen(popa) - 1;

	/* Et on termine par l'instruction JMP qui donnera la main au programme hote */
	ft_memcpy(ptr, jmp, ft_strlen(jmp) - 1);
}

void inject_code(unsigned char *f_mmaped, t_packer *pack)
{
	int				i;
	Elf32_Ehdr		*elf_begin;
	Elf32_Phdr		*elf_pt_load, *elf_pt_load_next;
	unsigned int	last_entry;
	int				jmp_adr;

	/* On fait pointer l'entête ELF sur le début du fichier */
	elf_begin = (void*)f_mmaped;
	/* On sauvegarde l'ancienne entrée du programme */
	last_entry = elf_begin->e_entry;

	/* Simple vérification du fichier */
	if ((unsigned int)pack->_size < (elf_begin->e_phoff + elf_begin->e_phnum * elf_begin->e_phentsize))
		printf("[-] ELF malformed.");

	/* On fait pointer l'entête de segment sur le début de la table de segment */

	elf_pt_load = (void*)f_mmaped + elf_begin->e_phoff;
	printf("[+] Find a free space under a PT_LOAD segment...n");
	/* On recherche le premier segment PT_LOAD */
	for (i = 0; i < elf_begin->e_phnum - 1; i++)
	{
		if (elf_pt_load->p_type == PT_LOAD)
			break;
		elf_pt_load++;
	}

	/* next pointe sur le prochain segment (l'entête) */
	elf_pt_load_next = elf_pt_load + 1;

	/* On vérifie que nous avons bien deux segments PT_LOAD */
	if (elf_pt_load_next->p_type != PT_LOAD || elf_pt_load->p_type != PT_LOAD)
		printf("[-] Don't found two PT_LOAD segment.");

	/* On vérifie que l'espace entre ces deux segments est suffisant pour y loger notre code */
	if (elf_pt_load->p_memsz != elf_pt_load->p_filesz || (CODE_OFFSET + CODE_SIZE) > (elf_pt_load_next->p_offset + elf_pt_load->p_offset))
		printf("[-] Don't found a free space.");
	printf("[+] Free space found : %d bytes.n", (elf_pt_load_next->p_offset) - (CODE_OFFSET));    

	printf("[+] Overwrite entry point (0x%.8x) programm with shellcode adress (0x%.8x)...n", last_entry, CODE_ADRESS);
	/* On écrase l'ancienne entrée du programme, par l'adresse où sera placé notre code */
	elf_begin->e_entry = (START_ADRESS + elf_pt_load->p_offset + elf_pt_load->p_memsz);

	printf("[+] Inject fake jmp to last entry point...n");
	/* On modifie l'instruction JMP pour qu'elle retourne au point d'entrée initial */
	jmp_adr = (last_entry - (elf_begin->e_entry + CODE_SIZE));    
	ft_memcpy(jmp + 1, &jmp_adr, sizeof(int));

	printf("[+] Inject code (%d bytes) at offset %.8x (virtual adress 0x%.8x)...n", CODE_SIZE, CODE_OFFSET, CODE_ADRESS);

	insert_code(f_mmaped + CODE_OFFSET);

	/* On augmente la taille du segment (dans l'entête ELF) où l'on a placé notre shellcode */
	printf("[+] Update segment size...n");
	elf_pt_load->p_memsz += CODE_SIZE;
	elf_pt_load->p_filesz += CODE_SIZE;
}