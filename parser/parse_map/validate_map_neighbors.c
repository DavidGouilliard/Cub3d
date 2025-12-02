/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_neighbors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:18:32 by oettaqi           #+#    #+#             */
/*   Updated: 2025/12/02 13:18:35 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map_internal.h"

static bool	is_closed_char(char c)
{
	return (c == '1' || c == ' ');
}

static void	fill_neighbors(t_parser_state *st, size_t y, size_t x, char n[4])
{
	n[0] = ' ';
	n[1] = ' ';
	n[2] = ' ';
	n[3] = ' ';
	if (x < trimmed_len(st->map_lines[y - 1]))
		n[0] = st->map_lines[y - 1][x];
	if (x < trimmed_len(st->map_lines[y + 1]))
		n[1] = st->map_lines[y + 1][x];
	if (x > 0)
		n[2] = st->map_lines[y][x - 1];
	if (x + 1 < trimmed_len(st->map_lines[y]))
		n[3] = st->map_lines[y][x + 1];
}

bool	space_neighbors_ok(t_parser_state *st, size_t y, size_t x, size_t end)
{
	char	n[4];

	if (x == 0 || x + 1 >= end)
		return (print_error("Espace adjacent a vide"), false);
	if (!wall_span_ok(st->map_lines[y - 1], x)
		|| !wall_span_ok(st->map_lines[y + 1], x))
		return (print_error("Carte non fermee verticalement"), false);
	fill_neighbors(st, y, x, n);
	if (!is_closed_char(n[0]) || !is_closed_char(n[1])
		|| !is_closed_char(n[2]) || !is_closed_char(n[3]))
		return (print_error("Espace adjacent a vide"), false);
	return (true);
}
