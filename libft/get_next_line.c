/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:42:45 by dagouill          #+#    #+#             */
/*   Updated: 2024/12/04 11:01:23 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	**gnl_leftover_slot(void)
{
	static char	*leftover;

	return (&leftover);
}

char	*trimline(char *line)
{
	int		i;
	char	*new_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	new_line = ft_substr(line, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*get_leftover(char *left_over)
{
	int		i;
	int		j;
	char	*new_leftover;

	i = 0;
	j = 0;
	if (!left_over)
		return (NULL);
	while (left_over[i] != '\n' && left_over[i])
		i++;
	if (left_over[i] == '\n')
		i++;
	while (left_over[i + j])
		j++;
	new_leftover = ft_substr(left_over, i, j);
	if (!new_leftover)
		return (free(left_over), NULL);
	return (free(left_over), new_leftover);
}

char	*ft_read_and_conc(int fd, char *left_over)
{
	char	*buf;
	int		bytes_read;
	char	*temp;

	if (!left_over)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && check_line(left_over) == 0)
	{
		buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (free(left_over), NULL);
		bytes_read = (int) read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(left_over), NULL);
		buf[bytes_read] = 0;
		temp = left_over;
		left_over = ft_strjoin(temp, buf);
		if (!left_over)
			return (free(temp), free(buf), NULL);
		free(temp);
		free(buf);
	}
	return (left_over);
}

char	*get_next_line(int fd)
{
	char			**slot;
	char			*left_over;
	char			*final_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	slot = gnl_leftover_slot();
	left_over = *slot;
	if (!left_over)
		left_over = ft_strdup("");
	left_over = ft_read_and_conc(fd, left_over);
	*slot = left_over;
	final_line = trimline(left_over);
	return (gnl_finalize_line(slot, final_line, left_over));
}
/*
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
int main()
{
	int fd = 0;
	int i = 0;
	char	*dest = NULL;

	fd = open("./test.txt", O_RDONLY);
	while (1)
	{
		i++;
		dest = get_next_line(fd);
		if (dest == NULL)
			break;
		printf("ligne %i : %s", i, dest);
		free(dest);
	}
	close(fd);
}
*/
/*
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
int main()
{
	char *dest;
	dest = get_next_line(0);
	printf("%s\n", dest);
	free(dest);
	return 0;
}
*/
