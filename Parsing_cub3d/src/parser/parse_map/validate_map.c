#include "parse_map_internal.h"

static bool	check_border_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (print_error("Carte ouverte sur le bord"), false);
		i++;
	}
	return (true);
}

static bool	handle_cell(t_parser_state *st, size_t y, size_t x, size_t end)
{
	char	c;

	c = st->map_lines[y][x];
	if (c == ' ')
	{
		if (!space_neighbors_ok(st, y, x, end))
			return (false);
	}
	else if (c == '0')
	{
		if (!zero_position_ok(st, y, x, end))
			return (print_error("Carte non fermee verticalement"), false);
	}
	else if (c != '1')
		return (print_error("Caractere invalide dans la carte"), false);
	return (true);
}

static bool	scan_row(t_parser_state *st, size_t y)
{
	size_t	start;
	size_t	end;
	size_t	x;

	if (!line_bounds_ok(st->map_lines[y], &start, &end))
		return (false);
	x = start;
	while (x < end)
	{
		if (!handle_cell(st, y, x, end))
			return (false);
		x++;
	}
	return (true);
}

bool	validate_map(t_parser_state *st)
{
	size_t	y;

	if (!st->map_lines || st->map_height == 0)
		return (print_error("Carte absente"), false);
	if (st->player_count != 1)
		return (print_error("Joueur absent ou multiple"), false);
	y = 0;
	while (y < st->map_height)
	{
		if (y == 0 || y + 1 == st->map_height)
		{
			if (!check_border_line(st->map_lines[y]))
				return (false);
		}
		else if (!scan_row(st, y))
			return (false);
		y++;
	}
	return (true);
}
