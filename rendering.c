/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:07:32 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 20:08:14 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_ray *ray, int x, t_data *img)
{
	double	wallheight;
	int		drawstart;
	int		drawend;
	int		y;

	wallheight = (double) WIN_H / ray->walldist;
	drawstart = WIN_H / 2 - (int) wallheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = (int) wallheight / 2 + WIN_H / 2;
	if (drawend >= WIN_H)
		drawend = WIN_H - 1;
	y = -1;
	while (y++ < drawstart)
			my_mlx_pixel_put(img, x, y, 0x87CEEB);
	while (y++ <= drawend)
			my_mlx_pixel_put(img, x, y, 033500);
	while (y++ < WIN_H)
			my_mlx_pixel_put(img, x, y, 0x332421);
}

void	render(t_game *game)
{
	t_ray	ray;
	int		i;

	i = -1;
	initialize_ray(&ray);
	while (++i < WIN_W)
	{
		ray = init_ray(game, i);
		dda_analysis(game, &ray);
		draw_column(&ray, i, &game->img);
	}
}
