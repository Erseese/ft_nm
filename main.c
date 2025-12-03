#include "ft_nm.h"

void    print_help()
{
    ft_printf("help : \nFunction Usage: nm [option(s)] [file(s)]\n\
List symbols in [file(s)] (a.out by default).\n The options are:\n\
-h, --help        Display this information\n\
nm: supported targets : elfx86_32, elfx64, object files, .so\n\
report bugs to : moi lol");
}

int	nm_fill_struct(char **argv, int argc, t_nm *global)
{
	t_hashmap flags = {0}; //static probablement
	char	keys[hash_size] = {'h'};
    char    c;

	global->i = 1;
	flags.key.i = *((int *)keys);
    c = parse_flags(argc, argv, &flags, &global->i);
	if (c != -1)
    {
        ft_printf("nm : invalid option -- '%c'", c);
        print_help();
        return 1;
    } 
    if (get_value(&flags, 'h') == 1)
    {
        print_help();
        return 1;
    } 
	global->flags = flags;
	return (0);
}

void    init(char **argv, int argc, t_nm *test)
{
    nm_fill_struct(argv, argc, test);
}

int main(int argc, char **argv)
{
    t_nm test;
    if (argc == 2)
    {
        if (ft_strcmp(argv[1], "--hdelp") == 0)
        {
            print_help();
            return 0;
        }
    }
    init(argv, argc, &test);


}