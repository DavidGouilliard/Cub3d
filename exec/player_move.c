/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:08:36 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 20:19:17 by dagouill         ###   ########.fr       */
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
void	straight_move(int keycode, t_game *game)
{
	double new_x;
	double new_y;

	new_x = 0.0;
	new_y = 0.0;
	if (keycode == XK_w)
		move_up(new_x, new_y, game);
	else if (keycode == XK_s)
		move_down(new_x, new_y, game);
	else if (keycode == XK_a)
		move_left(new_x, new_y, game);
	else if (keycode == XK_d)
		move_right(new_x, new_y, game);
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
		sin_angle = - player->sin_rot;

	player->dir_x = player->dir_x *cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x *sin_angle + player->dir_y * cos_angle;

	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

void	move_player(int keycode, t_game *game)
{
	if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		straight_move(keycode, game);
	else if (keycode == XK_Left)
		rotate_player(&game->player, -1);
	else if (keycode == XK_Right)
		rotate_player(&game->player, 1);
}

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

/*char	get_player_pos(t_game *g)*/
/*{*/
/*	int		y;*/
/*	int		x;*/
/*	char	c;*/
/**/
/*	y = 0;*/
/*	c = 0;*/
/*	while (y < g->height)*/
/*	{*/
/*		x = 0;*/
/*		while (g->map[y][x])*/
/*		{*/
/*			c = g->map[y][x];*/
/*			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')*/
/*			{*/
/*				g->player.x = (double)x + 0.5;*/
/*				g->player.y = (double)y + 0.5;*/
/*				g->map[y][x] = '0';*/
/*				return (c);*/
/*			}*/
/*			x++;*/
/*		}*/
/*		y++;*/
/*	}*/
/*	return (c);*/
/*}*/
