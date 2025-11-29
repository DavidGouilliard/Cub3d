/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:08:36 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:27:17 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(double new_x, double new_y, t_game *game)
{
	new_x = game->player.x + game->player.dir_x * game->player.move_speed;
	new_y = game->player.y + game->player.dir_y * game->player.move_speed;
	if (new_x < 0)
		new_x = 0.0001;
	if (new_y < 0)
		new_y = 0.0001;
	if (game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_down(double new_x, double new_y, t_game *game)
{
	new_x = game->player.x - game->player.dir_x * game->player.move_speed;
	new_y = game->player.y - game->player.dir_y * game->player.move_speed;
	if (new_x < 0)
		new_x = 0.0001;
	if (new_y < 0)
		new_y = 0.0001;
	if (game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_left(double new_x, double new_y, t_game *game)
{
	new_x = game->player.x - game->player.plane_x * game->player.move_speed;
	new_y = game->player.y - game->player.plane_y * game->player.move_speed;
	if (new_x < 0)
		new_x = 0.0001;
	if (new_y < 0)
		new_y = 0.0001;
	if (game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_right(double new_x, double new_y, t_game *game)
{
	new_x = game->player.x + game->player.plane_x * game->player.move_speed;
	new_y = game->player.y + game->player.plane_y * game->player.move_speed;
	if (new_x < 0)
		new_x = 0.0001;
	if (new_y < 0)
		new_y = 0.0001;
	if (game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	rotate_player(t_player *player, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	cos_angle = player->cos_rot;
	if (direction > 0)
		sin_angle = player->sin_rot;
	else
		sin_angle = -player->sin_rot;
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}
