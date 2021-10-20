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
		close(pack->_fd);
		free(pack->_content);
		return (-1);
	}
	return (0);
}

void	free_all(t_packer *pack)
{
	close(pack->_fd);
	free(pack->_content);
	free(pack);
}

int		main(int ac, char **av)
{
	t_packer	*pack;

	if (ac != 2 || !(pack = (t_packer *)malloc(sizeof(t_packer) * 1)))
	{
		ft_putstr_fd("Usage: ./woody_woodpacker [ELF64 file]\n", 2);
		return (1);
	}
	if (initialize_packer(pack, av[1]) == -1)
	{
		ft_putstr_fd("Usage: ./woody_woodpacker [ELF64 file]\n", 2);
		free(pack);
		return (1);
	}
	free_all(pack);
	return (0);
}