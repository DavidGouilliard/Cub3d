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

#include "cub3d.h"

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == XK_d || keycode == XK_a
		|| keycode == XK_w || keycode == XK_s
		|| keycode == XK_Left || keycode == XK_Right)
	{
		move_player(keycode, game);
		/*print_player(game);*/
	}
	return (0);
}

int	on_destroy(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
	return (0);
}

int	render_frame(void *param)
{
	t_game *game;

	game = (t_game *)param;

	render(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	update_fps(game);
	display_fps(game);
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, &on_keypress, game);
	mlx_hook(game->win_ptr, 17, 0, &on_destroy, game);
	mlx_loop_hook(game->mlx_ptr, &render_frame, game);
	mlx_loop(game->mlx_ptr);
}
