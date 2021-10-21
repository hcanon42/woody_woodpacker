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
