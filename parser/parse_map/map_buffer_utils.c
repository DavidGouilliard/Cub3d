/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_buffer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:01:47 by oettaqi           #+#    #+#             */
/*   Updated: 2025/12/02 10:01:49 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map_internal.h"

void	init_map_buffer(t_map_buffer *buf)
{
	buf->lines = NULL;
	buf->size = 0;
	buf->capacity = 0;
}

void	free_map_buffer(t_map_buffer *buf)
{
	size_t	i;

	if (!buf->lines)
		return ;
	i = 0;
	while (i < buf->size)
	{
		free(buf->lines[i]);
		i++;
	}
	free(buf->lines);
}
