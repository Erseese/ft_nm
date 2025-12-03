/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ersees <ersees@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:38:05 by ytouihar          #+#    #+#             */
/*   Updated: 2024/05/19 02:02:48 by ersees           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft_modif/libft.h"

# define hash_size 4
# define function_number 2

# define QUIET global->flags.value[3]
# define REVERSE global->flags.value[2]
# define STRING global->flags.value[1]
# define P		global->flags.value[0]

typedef struct s_hashmap
{
	union
	{
		char key[hash_size];
		int i;
	} key;
	int value[hash_size];
} t_hashmap;

typedef struct s_mapssl
{
    char    *name;
    void    (*fct)(char **, int);
} t_mapssl;

typedef struct s_linked
{
	int		state;
	int		fd;
	char	*text;
	char	*filename;
	struct s_linked *next;
}			t_linked;

typedef struct s_md5_context{
    uint64_t size;        // Size of input in bytes
    uint32_t buffer[4];   // Current accumulation of hash
    uint8_t input[64];    // Input to be used in the next step
    uint8_t digest[16];   // Result of algorithm
}		t_md5_context;

typedef struct s_md5
{
	t_hashmap	flags;
	char		*stdinput;
	int			i;
	t_linked	*files;
	uint8_t		digest[16];
}			t_md5;

typedef struct s_sha256
{
	t_hashmap	flags;
}			t_sha256;


#endif