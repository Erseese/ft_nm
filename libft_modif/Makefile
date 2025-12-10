NAME = libft.a

SRCS =	ft_strlen.c ft_strjoin.c ft_split.c ft_strncmp.c ft_substr.c ft_memset.c ft_strcmp.c ft_strdup.c ft_memcmp.c ft_memcpy.c ft_memchr.c ft_memmove.c

OBJS = ${SRCS:.c=.o}
INCS = includes

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${NAME} : ${OBJS}
	ar rc ${NAME} ${OBJS}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.phony : all clean fclean re