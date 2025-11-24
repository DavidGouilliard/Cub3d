/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 08:42:50 by dagouill          #+#    #+#             */
/*   Updated: 2024/11/10 10:31:14 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nb(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dest;
	int		i;
	long	nb;

	nb = (long) n;
	len = len_nb(n);
	i = 0;
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{
		dest[i] = '-';
		i++;
		nb = -nb;
	}
	dest[len] = '\0';
	while (len > i)
	{
		dest[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (dest);
}
