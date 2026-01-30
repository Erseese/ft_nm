NAME = ft_nm
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.
RM = rm -rf
FILE = nm
OBJDIR = obj
SRCS = main.c ${FILE}/options/flags.c ${FILE}/print/printhdr.c ${FILE}/parse/parse_ehdr.c ${FILE}/parse/ehdr_accessor.c \
		${FILE}/parse/phdr_accessor.c ${FILE}/parse/shdr_accessor.c ${FILE}/ft_nm.c \
		

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
LIBFT = libft_modif/libft.a
PRINTF = ft_printf/libftprintf.a


all : ${NAME}

start :
	make all -C libft_modif
	make all -C ft_printf

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


#.c.o:
#	cc $(CFLAGS) -g3 -c -o $@ $< 

${NAME} : start $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)


clean :
	$(RM) $(OBJDIR)
	make clean -C ft_printf
	make clean -C libft_modif

fclean : clean
	$(RM) $(NAME)
	make fclean -C ft_printf
	make fclean -C libft_modif


perso : all clean

re : fclean all


.phony : all clean fclean re perso