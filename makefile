##---------------------------------MAKEFILE-------------------------------------

#====================================OBJS=======================================
OBJS		=	${SRCS:.cpp=.o}


#====================================SRCS=======================================
SRCS			=	srcs/main.cpp		\
					srcs/packer.cpp


#=============================FLAGS AND COMPILERS===============================
CCPP			=	clang++
CPPFLAGS		=	-Wall -Wextra -Werror -I .includes/
NAME			=	woody_woodpacker
NAME_LIB		=	./libft/libft.a


#================================AVAILABLE RULES================================
#-----
all:		make_libs $(NAME)

#-----
make_libs:
		$(MAKE) add -C ./libft/

#-----
$(NAME):	${OBJS}
		${CCPP} ${CPPFLAGS} -o ${NAME} ${OBJS} ${NAME_LIB}
#-----
clean:
		$(MAKE) clean -C ./libft/
		rm -f ${OBJS}

#-----
fclean:		clean
		$(MAKE) fclean -C ./libft/
		rm -f ${NAME}

#-----
re:		fclean all

#-----
.PHONY:		all clean fclean re