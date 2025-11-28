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
	bool	left;
	bool	right;

	len = trimmed_len(line);
	if (len == 0)
		return (false);
	if (x >= len)
		x = len - 1;
	left = false;
	i = (ssize_t)x;
	while (i >= 0)
	{
		if (line[i] == '1')
		{
			left = true;
			break ;
		}
		if (i == 0)
			break ;
		i--;
	}
	right = false;
	i = (ssize_t)x;
	while ((size_t)i < len)
	{
		if (line[i] == '1')
		{
			right = true;
			break ;
		}
		if ((size_t)i + 1 == len)
			break ;
		i++;
	}
	return (left && right);
}

bool	space_neighbors_ok(t_parser_state *st, size_t y, size_t x, size_t end)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (x == 0 || x + 1 >= end)
		return (print_error("Espace adjacent a vide"), false);
	if (!wall_span_ok(st->map_lines[y - 1], x)
		|| !wall_span_ok(st->map_lines[y + 1], x))
		return (print_error("Carte non fermee verticalement"), false);
	up = (x < trimmed_len(st->map_lines[y - 1])) ? st->map_lines[y - 1][x] : ' ';
	down = (x < trimmed_len(st->map_lines[y + 1])) ? st->map_lines[y + 1][x] : ' ';
	left = (x == 0) ? ' ' : st->map_lines[y][x - 1];
	right = (x + 1 < trimmed_len(st->map_lines[y])) ? st->map_lines[y][x + 1] : ' ';
	if ((up != '1' && up != ' ')
		|| (down != '1' && down != ' ')
		|| (left != '1' && left != ' ')
		|| (right != '1' && right != ' '))
		return (print_error("Espace adjacent a vide"), false);
	return (true);
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
