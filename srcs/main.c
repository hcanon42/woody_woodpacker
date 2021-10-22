# include "../includes/packer.h"

void	free_all(t_packer *pack)
{
	if (pack)
	{
		if (pack->_fd)
			close(pack->_fd);
		if (pack->_content)
			free(pack->_content);
		free(pack);
	}
}

int		create_woody(t_packer *pack)
{
	int		fd;

	fd = open("woody", O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		return (-1);
	if (write(fd, pack->_content, pack->_size) == -1)
	{
		close(fd);
		return (1);
	}
	close(pack->_fd);
	pack->_fd = fd;
	return (0);
}

void	ft_encrypt(char *to_encrypt, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		to_encrypt[i] = to_encrypt[i] + 0;
		i++;
	}
}

int		main(int ac, char **av)
{
	t_packer	*pack;
    unsigned char *f_mmaped = NULL;

	if (ac != 2 || !(pack = (t_packer *)malloc(sizeof(t_packer) * 1))
				|| initialize_packer(pack, av[1]) == -1)
	{
		ft_putstr_fd("Usage: ./woody_woodpacker [ELF64 file]\n", 2);
		free_all(pack);
		return (1);
	}
	if (create_woody(pack) == -1)
	{
		ft_putstr_fd("Error while creating or writing in \"woody\" file\n", 2);
		free_all(pack);
		return (1);
	}

    printf("[+] Mmap file in memory...\n");
    if((f_mmaped = mmap(NULL, pack->_size, PROT_READ | PROT_WRITE, MAP_SHARED, pack->_fd, 0)) == NULL)
    {
		ft_putstr_fd("Error while mmap\n", 2);
		free_all(pack);
		return (1);
	}
    if (inject_code(f_mmaped, pack) == -1)
	{
		ft_putstr_fd("Error while injecting code\n", 2);
		free_all(pack);
		return (1);
	}
    if (munmap(f_mmaped, pack->_size) == -1)
    {
		ft_putstr_fd("Error while munmap\n", 2);
		free_all(pack);
		return (1);
	}

	free_all(pack);
	return (0);
}