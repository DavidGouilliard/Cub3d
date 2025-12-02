/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:02:18 by oettaqi           #+#    #+#             */
/*   Updated: 2025/12/02 10:02:27 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map_internal.h"

size_t	trimmed_len(const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && ft_isspace(line[len - 1]))
		len--;
	return (len);
}

bool	line_bounds_ok(const char *line, size_t *start, size_t *end)
{
	*start = 0;
	while (line[*start] == ' ')
		(*start)++;
	*end = trimmed_len(line);
	if (*start == *end || line[*start] != '1' || line[*end - 1] != '1')
		return (print_error("Carte non fermee sur les bords"), false);
	return (true);
}

bool	wall_span_ok(const char *line, size_t x)
{
	size_t	len;
	ssize_t	i;

	len = trimmed_len(line);
	if (len == 0)
		return (false);
	if (x >= len)
		x = len - 1;
	i = (ssize_t)x;
	while (i >= 0 && line[i] != '1')
		i--;
	if (i < 0)
		return (false);
	i = (ssize_t)x;
	while ((size_t)i < len && line[i] != '1')
		i++;
	return ((size_t)i < len);
}

bool	zero_position_ok(t_parser_state *st, size_t y, size_t x, size_t end)
{
	if (x == 0 || x + 1 >= end)
		return (false);
	if (!wall_span_ok(st->map_lines[y - 1], x)
		|| !wall_span_ok(st->map_lines[y + 1], x))
		return (false);
	return (true);
}
