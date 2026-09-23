#include "ft_nm.h"

int get_value(t_hashmap *hash, char key)
{
	for (int i = 0; i < hash_size; ++i)
	{
        printf("%c : test\n", hash->key.key[i]);
		if (hash->key.key[i] == key)
        {
        printf("%c, %d : test\n", hash->key.key[i], hash->value[i]);
			return (hash->value[i]);
        }
    }
	return (-1);
}

static void set_value(t_hashmap *hash, char key, int value)
{
	for (int i = 0; i < hash_size; ++i)
	{
		if (hash->key.key[i] == key)
			hash->value[i] = value;
	}
}

static int good_flag(char *arguments, char *flag, t_hashmap *hash)
{
	int check;

	if (!arguments || arguments[0] != '-')
		return (-1);
	for (int i = 1; arguments[i]; i++)
	{
		check = 0;
		for (int j = 0; flag[j]; j++)
		{
			if (arguments[i] == flag[j])
			{
				check = 1;
				set_value(hash, flag[j], 1);
			}
		}
		if (check == 0)
			return (arguments[i]);
	}
	return (0);
}

int parse_flags(int argc, char **argv, t_hashmap *flags, int *i)
{
	char *flag = "h";
    char err;
	while(*i < argc)
	{
		if ((err = good_flag(argv[*i], flag, flags)) == 1)
        {
            return err;
        }
        *i += 1;
	}
    return 0;
}