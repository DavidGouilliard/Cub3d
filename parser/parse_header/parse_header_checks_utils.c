/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_checks_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:05:12 by oettaqi           #+#    #+#             */
/*   Updated: 2025/12/02 13:05:15 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header_internal.h"

bool	texture_is_xpm(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (true);
	if (path[len - 4] != '.' || path[len - 3] != 'x'
		|| path[len - 2] != 'p' || path[len - 1] != 'm')
		return (true);
	return (false);
}

bool	texture_unreadable(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (true);
	close(fd);
	return (false);
}
