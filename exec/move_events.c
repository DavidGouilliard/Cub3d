/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:11:20 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:17:02 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_rotate(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

int	on_mouse_move(int x, int y, t_game *game)
{
	int		center;
	int		diff_x;
	double	delta;

	(void)y;
	center = WIN_W / 2;
	if (x == center)
		return (0);
	diff_x = x - center;
	delta = diff_x * MOUSE_SPEED;
	mouse_rotate(&game->player, delta);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, center, WIN_H / 2);
	return (0);
}

void	scale_move_to_fps(t_game *game)
{
	double	new_angle;

	game->last_time = game->current_time;
	game->current_time = get_time();
	game->frame_time = game->current_time - game->last_time;
	if (game->frame_time > 0.05)
		game->frame_time = 0.05;
	new_angle = ROT_SPEED * game->frame_time;
	game->player.move_speed = MOVE_SPEED * game->frame_time;
	game->player.cos_rot = cos(new_angle);
	game->player.sin_rot = sin(new_angle);
}

void	process_input(t_game *game)
{
	if (game->keys.up)
		move_up(0, 0, game);
	if (game->keys.down)
		move_down(0, 0, game);
	if (game->keys.left)
		move_left(0, 0, game);
	if (game->keys.right)
		move_right(0, 0, game);
	if (game->keys.r_left)
		rotate_player(&game->player, -1);
	if (game->keys.r_right)
		rotate_player(&game->player, 1);
}
