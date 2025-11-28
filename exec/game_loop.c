/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:09:41 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 20:10:14 by dagouill         ###   ########.fr       */
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
	/*if (direction > 0)*/
	/*	sin_angle = player->sin_rot;*/
	/*else*/
	/*	sin_angle = - player->sin_rot;*/

	player->dir_x = player->dir_x *cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x *sin_angle + player->dir_y * cos_angle;

	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}
int	on_mouse_move(int x, int y, t_game *game)
{
	(void)y;

	int		center;
	int		diff_x;
	double	delta;

	center = WIN_W / 2;
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
	new_angle = ROT_SPEED * game->frame_time;
	game->player.move_speed = MOVE_SPEED * game->frame_time;
	game->player.cos_rot = cos(new_angle);
	game->player.sin_rot = sin(new_angle);
}

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == XK_w)
		game->keys.up = 1;
	else if (keycode == XK_s)
		game->keys.down = 1;
	else if (keycode == XK_a)
		game->keys.left = 1;
	else if (keycode == XK_d)
		game->keys.right = 1;
	else if (keycode == XK_Left)
		game->keys.r_left = 1;
	else if (keycode == XK_Right)
		game->keys.r_right = 1;
	return (0);
}

int	on_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.up = 0;
	else if (keycode == XK_s)
		game->keys.down = 0;
	else if (keycode == XK_a)
		game->keys.left = 0;
	else if (keycode == XK_d)
		game->keys.right = 0;
	else if (keycode == XK_Left)
		game->keys.r_left = 0;
	else if (keycode == XK_Right)
		game->keys.r_right = 0;
	return (0);
}

int	on_destroy(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
	return (0);
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

int	render_frame(void *param)
{
	t_game *game;

	game = (t_game *)param;

	scale_move_to_fps(game);
	process_input(game);
	render(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	update_fps(game);
	display_fps(game);
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 6, 1L << 6, &on_mouse_move, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, &on_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, &on_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 0, &on_destroy, game);
	mlx_loop_hook(game->mlx_ptr, &render_frame, game);
	mlx_loop(game->mlx_ptr);
}
