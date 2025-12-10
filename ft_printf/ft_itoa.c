/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ersees <ersees@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:30:38 by ytouihar          #+#    #+#             */
/*   Updated: 2024/05/18 10:48:23 by ersees           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_taille(unsigned long int nb, unsigned long int base)
{
	long int	li;

	li = 0;
	
	while (nb > base - 1)
	{
		li++;
		nb = nb / base;
	}
	li++;
	return (li);
}

char	*ft_itoa(unsigned long int nb, unsigned long int base)
{
	int		taille;
	char	*res;

	taille = ft_taille(nb, base);
	res = malloc((1 + taille) * sizeof(char));
	if (res == NULL)
		return (0);
	res[taille] = '\0';
	taille--;
	while (base - 1 < nb)
	{
		res[taille] = "0123456789abcdef"[nb % base];
		nb = nb / base;
		taille--;
	}
	res[taille] = "0123456789abcdef"[nb % base];
	nb = nb / base;
	return (res);
}

char	*ft_itoa_maj(unsigned long int nb, unsigned long int base)
{
	long int	taille;
	char		*res;

	taille = ft_taille(nb, base);
	res = malloc((1 + taille) * sizeof(char));
	if (res == NULL)
		return (0);
	res[taille] = '\0';
	taille--;
	while (base - 1 < nb)
	{
		res[taille] = "0123456789ABCDEF"[nb % base];
		nb = nb / base;
		taille--;
	}
	res[taille] = "0123456789ABCDEF"[nb % base];
	nb = nb / base;
	return (res);
}

int	ft_taille2(long int nb, long int base)
{
	long int	li;

	li = 0;
	if (nb < 0)
	{
		nb = -nb;
		li++;
	}
	while (nb > base - 1)
	{
		li++;
		nb = nb / base;
	}
	li++;
	return (li);
}

char	*ft_itoa2(long int nb, long int base)
{
	int		taille;
	char	*res;

	taille = ft_taille2(nb, base);
	res = malloc((1 + taille) * sizeof(char));
	if (res == NULL)
		return (0);
	res[taille] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	taille--;
	while (base - 1 < nb)
	{
		res[taille] = "0123456789abcdef"[nb % base];
		nb = nb / base;
		taille--;
	}
	res[taille] = "0123456789abcdef"[nb % base];
	nb = nb / base;
	return (res);
}


char    *ft_itoa_base_ul(unsigned long nbr, char *base)
{
    char            buffer[65];
    size_t             base_len = ft_strlen(base);
    int             i = 64;

    buffer[i] = '\0';
    if (nbr == 0)
        buffer[--i] = base[0];

    while (nbr > 0)
    {
        buffer[--i] = base[nbr % base_len];
        nbr /= base_len;
    }
    return (ft_strdup(&buffer[i]));
}
