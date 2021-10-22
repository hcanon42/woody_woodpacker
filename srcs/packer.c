# include "../includes/packer.h"

const char	shellcode[] = "xb8x01x00x00x00xbfx01x00x00x00x48xbex00x20x40x00x00x00x00x00xbax0ex00x00x00x0fx05xb8x3cx00x00x00xbfx00x00x00x00x0fx05";
char		jmp[] = "xe9xffxffxffxff";
char		pusha[] = "x60";
char		popa[] = "x61";

# define CODE_OFFSET (elf_pt_load->p_offset + elf_pt_load->p_memsz)
# define CODE_ADRESS (old_entry + CODE_OFFSET)

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

int		is_space_available(Elf64_Phdr *elf_pt_load, size_t code_size)
{
	Elf64_Phdr		*elf_pt_load_next;

	elf_pt_load_next = elf_pt_load + 1;
	if (elf_pt_load->p_type == PT_LOAD && elf_pt_load_next->p_type == PT_LOAD)
		if (elf_pt_load->p_memsz != elf_pt_load->p_filesz ||
			(CODE_OFFSET + code_size) > (elf_pt_load_next->p_offset + elf_pt_load->p_offset))
		return (1);
	return (0);
}

void	insert_code(unsigned char *ptr)
{
	ft_memcpy(ptr, pusha, ft_strlen(pusha));
	ptr += ft_strlen(pusha);
	ft_memcpy(ptr, shellcode, ft_strlen(shellcode));
	ptr += ft_strlen(shellcode);
	ft_memcpy(ptr, popa, ft_strlen(popa));
	ptr += ft_strlen(popa);
	ft_memcpy(ptr, jmp, ft_strlen(jmp));
}

int		inject_code(unsigned char *f_mmaped, t_packer *pack)
{
	int				jmp_adr;
	unsigned int	old_entry;
	size_t			code_size;
	Elf64_Ehdr		*elf_begin;
	Elf64_Phdr		*elf_pt_load;
	Elf64_Phdr		*elf_pt_load_next;

	code_size = ft_strlen(shellcode) + ft_strlen(jmp) + ft_strlen(pusha) + ft_strlen(popa);
	elf_begin = (void*)f_mmaped;
	old_entry = elf_begin->e_entry;
	printf("entry point = %.8x\n", old_entry);
	if ((unsigned int)pack->_size < (elf_begin->e_phoff + elf_begin->e_phnum * elf_begin->e_phentsize))
	{
		ft_putstr("[-] ELF malformed.\n");
		return (-1);
	}
	elf_pt_load = (void*)f_mmaped + elf_begin->e_phoff;	/* going to beginning of segment */

	ft_putstr("[+] Finding a free space under a PT_LOAD segment...\n");
	for (int i = 0; i < elf_begin->e_phnum - 2; i++) 	/* searching for PT_LOAD */
	{
    //   if (elf_pt_load->p_type == PT_LOAD && elf_pt_load->p_flags & 0x011)
	// {
	//   printf ("+ Found .text segment (#%d)\n", i);
	//   text_seg = elf_pt_load;
	//   text_end = elf_pt_load->p_offset + elf_pt_load->p_filesz;
	// }
    //   else
	// {
	//   if (elf_pt_load->p_type == PT_LOAD && 
	//       (elf_pt_load->p_offset - text_end) < gap) 
	//     {
	//       printf ("   * Found LOAD segment (#%d) close to .text (offset: 0x%x)\n",
	// 	      i, (unsigned int)elf_pt_load->p_offset);
	//       gap = elf_pt_load->p_offset - text_end;
	//     }
	// }
		elf_pt_load = (Elf64_Phdr *) ((unsigned char*) elf_pt_load 
					+ (unsigned int) elf_begin->e_phentsize);
    }
	if (!(elf_pt_load + 1) || is_space_available(elf_pt_load, code_size) != 1)
	{
		ft_putstr("[-] Didn't found enough space.\n");
		return (-1);
	}
	elf_pt_load_next = elf_pt_load + 1;
	ft_printf("[+] Free space found : %d bytes.\n", (elf_pt_load_next->p_offset) - (CODE_OFFSET));

	ft_printf("[+] Overwriting entry point (0x%.8x) program with shellcode adress (0x%.8x)...\n", old_entry, CODE_ADRESS);
	elf_begin->e_entry = (old_entry + elf_pt_load->p_offset + elf_pt_load->p_memsz);	/* changing old entry of the code by the address of ours */

	ft_putstr("[+] Injecting fake jmp to last entry point...\n");
	jmp_adr = (old_entry - (elf_begin->e_entry + code_size)); /* modifying JMP to get back to original entry */
	ft_memcpy(jmp + 1, &jmp_adr, sizeof(int));

	ft_printf("[+] Injecting code (%ld bytes) at offset %.8x (virtual adress 0x%.8x)...\n", code_size, CODE_OFFSET, CODE_ADRESS);
	insert_code(f_mmaped + CODE_OFFSET);

	ft_putstr("[+] Updating segment size...\n");
	elf_pt_load->p_memsz += code_size;
	elf_pt_load->p_filesz += code_size;
	return (0);
}
