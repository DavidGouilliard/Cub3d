/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 06:17:03 by dagouill          #+#    #+#             */
/*   Updated: 2024/11/10 08:40:54 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static	char	**free_everything(char **dest, int j)
{
	while (j >= 0)
	{
		if (dest[j])
			free(dest[j]);
		j--;
	}
	free(dest);
	return (NULL);
}

static	char	**split_words(char const *s, char c, char **dest, int j)
{
	int	i;
	int	len;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		len = 0;
		if (s[i] != c)
		{
			while (s[len + i] && s[len + i] != c)
				len++;
			dest[j] = ft_substr(s, i, len);
			if (dest[j] == NULL)
				return (free_everything(dest, j));
			j++;
			i = len + i;
		}
		else
			i++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	dest = NULL;
	dest = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (dest == NULL)
		return (NULL);
	if (!(split_words(s, c, dest, j)))
		return (NULL);
	return (dest);
}
