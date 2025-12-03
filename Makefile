NAME = ft_nm
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
SRCS = main.c flags.c ft_nm.c
OBJS = ${SRCS:.c=.o}
LIBFT = libft_modif/libft.a
PRINTF = ft_printf/libftprintf.a

all : ${NAME}

start :
	make all -C libft_modif
	make all -C ft_printf

.c.o:
	cc $(CFLAGS) -g3 -c -o $@ $< 

${NAME} : start $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C ft_printf
	make fclean -C libft_modif

clean :
	$(RM) $(OBJS)
	make clean -C ft_printf
	make clean -C libft_modif

perso : all clean

re : fclean all


.phony : all clean fclean re perso