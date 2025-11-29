/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:08 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:24:18 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_dir(t_game *g, char C)
{
	if (C == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1;
	}
	else if (C == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
	}
	else if (C == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
	}
	else if (C == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
	}
}

void	init_player(t_game *g, t_parser_state state)
{
	g->player.x = (double) state.player_x + 0.5;
	g->player.y = (double) state.player_y + 0.5;
	set_player_dir(g, state.player_dir);
	g->player.plane_x = -g->player.dir_y * FOV;
	g->player.plane_y = g->player.dir_x * FOV;
	g->player.move_speed = MOVE_SPEED;
	g->player.cos_rot = cos(ROT_SPEED);
	g->player.sin_rot = sin(ROT_SPEED);
}
