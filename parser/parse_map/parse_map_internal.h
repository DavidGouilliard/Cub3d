#ifndef PARSE_MAP_INTERNAL_H
# define PARSE_MAP_INTERNAL_H

# include "../parse_header/parse_header_internal.h"

typedef struct s_map_buffer
{
	char	**lines;
	size_t	size;
	size_t	capacity;
}	t_map_buffer;

void	init_map_buffer(t_map_buffer *buf);
void	free_map_buffer(t_map_buffer *buf);
size_t	trimmed_len(const char *line);
bool	line_bounds_ok(const char *line, size_t *start, size_t *end);
bool	wall_span_ok(const char *line, size_t x);
bool	space_neighbors_ok(t_parser_state *st, size_t y, size_t x, size_t end);
bool	zero_position_ok(t_parser_state *st, size_t y, size_t x, size_t end);

#endif
