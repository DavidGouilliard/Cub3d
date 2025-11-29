/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:09:41 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:17:47 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	on_destroy(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
	return (0);
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

int	render_frame(void *param)
{
	t_game	*game;

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
