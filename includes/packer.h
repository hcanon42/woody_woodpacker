#ifndef PACKER_H
# define PACKER_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct	s_packer
{
	char		*_content;
	int			_fd;
	size_t		_size;
	int			_type;
}				t_packer;

void				openFile(char *to_read, t_packer *pack);

#endif