# include "../includes/packer.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./woody_woodpacker [ELF64 file]" << std::endl;
		return (-1);
	}
	packer	pack(av[1]);
	if (pack.getFileType().compare("ELF64") != 0)
	{
		std::cout << "Usage: ./woody_woodpacker [ELF64 file]" << std::endl;
		return (-1);
	}
	return (0);
}