#ifndef PACKER_H
# define PACKER_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <elf.h>
# include <errno.h>
# include "../libft/libft.h"
 
const char	shellcode[] = "xb8x01x00x00x00xbfx01x00x00x00x48xbex00x20x40x00x00x00x00x00xbax0ex00x00x00x0fx05xb8x3cx00x00x00xbfx00x00x00x00x0fx05";
char		jmp[] = "xe9xffxffxffxff";
char		pusha[] = "x60";
char		popa[] = "x61";
 
/* Sur mon système, l'adresse de base où sera mappé le fichier est 0x08048000 */
# define START_ADRESS (unsigned int) 0x08048000
# define CODE_SIZE (ft_strlen(shellcode) - 1 + ft_strlen(jmp) - 1 + ft_strlen(pusha) - 1 + ft_strlen(popa) - 1)
# define CODE_OFFSET (elf_pt_load->p_offset + elf_pt_load->p_memsz)
# define CODE_ADRESS (START_ADRESS + CODE_OFFSET)

typedef struct	s_packer
{
	char		*_content;
	int			_fd;
	size_t		_size;
	int			_type;
}				t_packer;

void				openFile(char *to_read, t_packer *pack);
int					initialize_packer(t_packer *pack, char *file_to_open);
void				inject_code(unsigned char *f_mmaped, t_packer *pack);

#endif