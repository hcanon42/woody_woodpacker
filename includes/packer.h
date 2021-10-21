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
 
const char shellcode[] = "xb8 x01 x00 x00 x00 xbf x01 x00 x00 x00 x48 xbe x00 x20 x40 x00 x00 x00 x00 x00 xba x0e x00 x00 x00 x0f x05 xb8 x3c x00 x00 x00 xbf x00 x00 x00 x00 x0f x05";
char jmp[] = "xe9xffxffxffxff";                      
char pusha[] = "x60";
char popa[] = "x61";
 
/* Sur mon système, l'adresse de base où sera mappé le fichier est 0x08048000 */
# define START_ADRESS (unsigned int) 0x08048000
# define CODE_SIZE (sizeof(shellcode)-1 + sizeof(jmp)-1 + sizeof(pusha)-1 + sizeof(popa)-1)
# define CODE_OFFSET (phdr->p_offset + phdr->p_memsz)
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