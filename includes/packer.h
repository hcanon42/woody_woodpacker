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


typedef struct	s_packer
{
	char		*_content;
	int			_fd;
	size_t		_size;
	int			_type;
}				t_packer;

void				openFile(char *to_read, t_packer *pack);
int					initialize_packer(t_packer *pack, char *file_to_open);
int					inject_code(unsigned char *f_mmaped, t_packer *pack);

#endif