/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:57:35 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 19:59:51 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_game *game)
{
	int	y;
	int	x;

	ft_putstr_fd("Map state:\n", 1);
	for (y = 0; y < game->height; y++)
	{
		x = 0;
		while (game->map[y][x])
		{
			write(1, &game->map[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
	}
}

void	print_player(t_game *game)
{
	ft_putstr_fd("Player position: ", 1);
	ft_putnbr_fd((int)game->player.x, 1);
	write(1, ", ", 2);
	ft_putnbr_fd((int)game->player.y, 1);
	write(1, "\n", 1);
	ft_putstr_fd("Player direction: ", 1);
	ft_putnbr_fd((int)(game->player.dir_x * 100), 1);
	write(1, ", ", 2);
	ft_putnbr_fd((int)(game->player.dir_y * 100), 1);
	write(1, "\n", 1);
}

double	get_time(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	display_fps(t_game *game)
{
	char	*fps_str;
	char	*buf;

	fps_str = ft_itoa((int)game->fps);
	if (!fps_str)
		return ;
	buf = ft_strjoin("FPS: ", fps_str);
	if (!buf)
	{
		free(fps_str);
		return ;
	}
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0x00FF00, buf);
	free(fps_str);
	free(buf);
}

void	update_fps(t_game *game)
{
	double current_time;

	current_time = get_time();
	game->frames++;
	if (current_time - game->last_time >= 1.0)
	{
		game->fps = game->frames / (current_time - game->last_time);
		game->frames = 0;
		game->last_time = current_time;
	}
}
