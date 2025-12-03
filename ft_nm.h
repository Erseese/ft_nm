#ifndef FT_NM
# define FT_NM

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft_modif/libft.h"
# include "ft_printf/ft_printf.h"

# define hash_size 1

typedef struct s_hashmap
{
	union
	{
		char key[hash_size];
		int i;
	} key;
	int value[hash_size];

} t_hashmap;


typedef struct s_nm
{
    t_hashmap   flags;
    int i;

} t_nm;


int    parse_flags(int argc, char **argv, t_hashmap *flags, int *i);
int     get_value(t_hashmap *hash, char key);
void    print_help();

#endif