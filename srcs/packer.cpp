# include "../includes/packer.hpp"

packer::packer() : _file_type(""), _file_size(0), _fd(-1), _content(NULL)
{
}

packer::packer(char *str) : _file_type(""), _file_size(0), _fd(-1), _content(NULL)
{
	this->_fd = open(str, O_RDONLY);
	if (this->_fd = -1)
	{
		this->_file_type = "ERROR";
		return ;
	}
}

packer::packer(packer const &ref) : _file_type(ref.getFileType()), _file_size(ref.getFileSize()), _fd(ref.getFd()), _content(ref.getFileContent())
{
}

packer::~packer()
{
}

packer		&packer::operator=(packer const &rhs)
{
	this->_file_size = rhs.getFileSize();
	this->_file_type = rhs.getFileType();
	return (*this);
}

std::string	packer::getFileType() const
{
	return (this->_file_type);
}

void		packer::setFileType(std::string file_type)
{
	this->_file_type = file_type;
}

char		*packer::getFileContent() const
{
	return (this->_content);
}

void		packer::setFileContent(char *content)
{
	this->_content = content;
}

int			packer::getFd() const
{
	return (this->_fd);
}

void		packer::setFd(int fd)
{
	this->_fd = fd;
}

int			packer::getFileSize() const
{
	return (this->_file_size);
}

void		packer::setFileSize(int file_size)
{
	this->_file_size = file_size;
}

