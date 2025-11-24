/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 05:31:32 by dagouill          #+#    #+#             */
/*   Updated: 2024/11/10 06:55:11 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_set(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char		*dest;
	int			i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (check_set(set, s1[i]))
		s1++;
	len = ft_strlen(s1);
	while (check_set(set, s1[len - 1]) && len > 0)
		len--;
	dest = (char *) ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	*dest = 0;
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
