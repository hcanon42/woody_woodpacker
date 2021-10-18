##---------------------------------MAKEFILE-------------------------------------

#====================================OBJS=======================================
OBJS		=	${SRCS:.cpp=.o}


#====================================SRCS=======================================
SRCS			=	srcs/main.cpp		\
					srcs/packer.cpp


#=============================FLAGS AND COMPILERS===============================
CCPP			=	clang++
CPPFLAGS		=	-m64 -Wall -Wextra -Werror -I .includes/
NAME			=	woody_woodpacker


#================================AVAILABLE RULES================================
#-----
all:		$(NAME)

#-----
$(NAME):	${OBJS}
		${CCPP} ${CPPFLAGS} -o ${NAME} ${OBJS}

#-----
clean:
		rm -f ${OBJS}
		rm -f ${OBJS_SHUFFLE}

#-----
fclean:		clean
		rm -f ${NAME}
		rm -f ${NAME_SHUFFLE}

#-----
re:		fclean all

#-----
.PHONY:		all clean fclean re
