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
    memcpy(ptr, pusha, sizeof(pusha)-1);
    ptr += sizeof(pusha)-1;
   
    /* On copie notre shellcode */
    memcpy(ptr, shellcode, sizeof(shellcode)-1);
    ptr += sizeof(shellcode)-1;
   
    /* On place l'instruction popa juste avant notre JMP */
    memcpy(ptr, popa, sizeof(popa)-1);
    ptr += sizeof(popa)-1;
   
    /* Et on termine par l'instruction JMP qui donnera la main au programme hote */
    memcpy(ptr, jmp, sizeof(jmp)-1);
}
 
void inject_code(unsigned char *f_mmaped, t_packer *pack)
{
    int i;
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr, *next;
    unsigned int last_entry;
    int jmp_adr;
   
    /* On fait pointer l'entête ELF sur le début du fichier */
    ehdr = (void*)f_mmaped;
    /* On sauvegarde l'ancienne entrée du programme */
    last_entry = ehdr->e_entry;
   
    /* Simple vérification du fichier */
    if((unsigned int)pack->_size < (ehdr->e_phoff + ehdr->e_phnum * ehdr->e_phentsize))
        printf("[-] ELF malformed.");
   
    /* On fait pointer l'entête de segment sur le début de la table de segment */
    phdr = (void*)f_mmaped + ehdr->e_phoff;
   
    printf("[+] Find a free space under a PT_LOAD segment...n");
   
    /* On recherche le premier segment PT_LOAD */
    for(i = 0; i < ehdr->e_phnum - 1; i++)
    {
        if(phdr->p_type == PT_LOAD)
            break;
        phdr++;
    }
    /* next pointe sur le prochain segment (l'entête) */
    next = phdr + 1;
   
    /* On vérifie que nous avons bien deux segments PT_LOAD */
    if(next->p_type != PT_LOAD || phdr->p_type != PT_LOAD)
        printf("[-] Don't found two PT_LOAD segment.");
   
    /* On vérifie que l'espace entre ces deux segments est suffisant pour y loger notre code */
    if(phdr->p_memsz != phdr->p_filesz || (CODE_OFFSET + CODE_SIZE) > (next->p_offset + phdr->p_offset))
        printf("[-] Don't found a free space.");
   
    printf("[+] Free space found : %d bytes.n", (next->p_offset) - (CODE_OFFSET));    
   
   
    printf("[+] Overwrite entry point (0x%.8x) programm with shellcode adress (0x%.8x)...n", last_entry, CODE_ADRESS);
    /* On écrase l'ancienne entrée du programme, par l'adresse où sera placé notre code */
    ehdr->e_entry = (START_ADRESS + phdr->p_offset + phdr->p_memsz);
   
 
    printf("[+] Inject fake jmp to last entry point...n");
    /* On modifie l'instruction JMP pour qu'elle retourne au point d'entrée initial */
    jmp_adr = (last_entry - (ehdr->e_entry + CODE_SIZE));    
    memcpy(jmp+1, &jmp_adr, sizeof(int));
   
    printf("[+] Inject code (%d bytes) at offset %.8x (virtual adress 0x%.8x)...n", CODE_SIZE, CODE_OFFSET, CODE_ADRESS);
   
    insert_code(f_mmaped + CODE_OFFSET);
   
    /* On augmente la taille du segment (dans l'entête ELF) où l'on a placé notre shellcode */
    printf("[+] Update segment size...n");
    phdr->p_memsz += CODE_SIZE;
    phdr->p_filesz += CODE_SIZE;    
   
}