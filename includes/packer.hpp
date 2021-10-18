#ifndef PACKER_HPP
# define PACKER_HPP

# include <vector>
# include <string>
# include <iostream>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>

class packer
{
	private:

		std::string	_file_type;
		int			_file_size;
		int			_fd;
		char		*_content;

	public:

		packer();
		packer(char *str);
		packer(packer const &ref);
		~packer();

		std::string		getFileType() const;
		void			setFileType(std::string file_type);
		char			*getFileContent() const;
		void			setFileContent(char *content);
		int				getFd() const;
		void			setFd(int fd);
		int				getFileSize() const;
		void			setFileSize(int file_size);

		packer		&operator=(packer const &rhs);
};

#endif