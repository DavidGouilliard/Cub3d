#include "parse_map_internal.h"


static bool	push_line_resize(t_map_buffer *buf)
{
	char	**tmp;
	size_t	newcap;
	size_t	i;

	if (buf->size != buf->capacity)
		return (true);
	if (buf->capacity == 0)
		newcap = 8;
	else
		newcap = buf->capacity * 2;
	tmp = ft_calloc(newcap, sizeof(char *));
	if (!tmp)
		return (false);
	i = 0;
	while (i < buf->size)
	{
		tmp[i] = buf->lines[i];
		i++;
	}
	free(buf->lines);
	buf->lines = tmp;
	buf->capacity = newcap;
	return (true);
}


static bool	push_line(t_map_buffer *buf, const char *line, t_parser_state *st)
{
	size_t	len;

	if (!push_line_resize(buf))
		return (false);
	buf->lines[buf->size] = ft_strdup(line);
	if (!buf->lines[buf->size])
		return (false);
	len = ft_strlen(line);
	if (len > st->map_width)
		st->map_width = len;
	buf->size++;
	st->map_height = buf->size;
	return (true);
}


static bool	handle_map_line(t_map_buffer *buf, t_parser_state *st, char *line)
{
	size_t	i;

	if (line[0] == '\0')
		return (print_error("Ligne vide dans la carte"), false);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (st->player_count++ > 0)
				return (print_error("Joueur multiple"), false);
			st->player_dir = line[i];
			st->player_x = (int)i;
			st->player_y = (int)buf->size;
			line[i] = '0';
		}
		else if (line[i] != '0' && line[i] != '1' && line[i] != ' ')
			return (print_error("Caractere invalide dans la carte"), false);
		i++;
	}
	return (push_line(buf, line, st));
}


static bool	finalize_map_parse(bool ok, t_parser_state *state, t_map_buffer *buf)
{
	if (!ok || state->player_count != 1)
	{
		if (ok && state->player_count != 1)
			print_error("Joueur absent ou multiple");
		free_map_buffer(buf);
		return (false);
	}
	state->map_lines = buf->lines;
	return (true);
}


bool	parse_map(int fd, t_parser_state *state, char *first_map_line)
{
	t_map_buffer	buf;
	char			*line;
	bool			ok;
	bool			ended;

	init_map_buffer(&buf);
	ok = handle_map_line(&buf, state, first_map_line);
	free(first_map_line);
	ended = false;
	while (ok && (line = get_next_line(fd)))
	{
		trim_newline(line);
		if (line_is_empty(line))
			ended = true;
		else if (ended)
			ok = (print_error("Contenu apres fin de carte"), false);
		else
			ok = handle_map_line(&buf, state, line);
		free(line);
	}
	return (finalize_map_parse(ok, state, &buf));
}
