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

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_line	init_line(t_line *line, int X, t_ray *ray, t_tex tex)
{
	line->x = X;
	line->y = 0;
	line->wallheight = (int) (WIN_H / ray->walldist);
	line->drawstart = WIN_H / 2 - (int) line->wallheight / 2;
	line->drawend = (int) line->wallheight / 2 + WIN_H / 2;
	line->tex_x = (int) (ray->wall_x * (double) tex.width);
	if (line->tex_x < 0)
		line->tex_x = 0;
	if (line->tex_x >= tex.width)
		line->tex_x = tex.width - 1;
	if (ray->horizontalwall == 0 && ray->raydirX < 0)
		line->tex_x = tex.width - 1 - line->tex_x;
	if (ray->horizontalwall == 1 && ray->raydirY > 0)
		line->tex_x = tex.width - 1 - line->tex_x;
	line->tex_y = 0;
	return (*line);
}

void	draw_tex_line(t_tex tex, t_line *line, t_data *img, char **dst)
{
	double				tex_step;
	double				tex_pos;
	unsigned int		color;
	long				offset;

	tex_step = 1.0 * tex.height / line->wallheight;
	tex_pos = (line->drawstart - WIN_H / 2 + line->wallheight / 2) * tex_step;
	line->y = line->drawstart;
	while (line->y <= line->drawend)
	{
		line->tex_y = (int) tex_pos & (tex.height - 1);
		tex_pos += tex_step;
		if (line->tex_y < 0)
			line->tex_y = 0;
		if (line->tex_y >= tex.height)
			line->tex_y = tex.height - 1;
		offset = ((long)line->tex_y * tex.line_length) + (line->tex_x * (tex.bits_per_pixel / 8));
		color = *(unsigned int *)(tex.addr + offset);
		*(unsigned int *)(*dst) = color;
		*dst += img->line_length;
		line->y++;
	}
}
void	draw_column(t_ray *ray, int x, t_game *game, t_tex tex)
{
	t_line 	line;
	char	*dst;

	dst = game->img.addr + (x * (game->img.bits_per_pixel / 8));
	line = init_line(&line, x, ray, tex);
	if (line.drawstart < 0)
		line.drawstart = 0;
	if (line.drawend >= WIN_H)
		line.drawend = WIN_H - 1;
	line.y = 0;
	while (line.y < line.drawstart)
	{
		*(unsigned int *)dst = game->colors[0];
		dst += game->img.line_length;
		line.y++;
	}
	draw_tex_line(tex, &line, &game->img, &dst);
	while (line.y < WIN_H)
	{
		*(unsigned int *)dst = game->colors[1];
		dst += game->img.line_length;
		line.y++;
	}
}

int	get_wall_direction(t_ray ray)
{
	 if (ray.horizontalwall == 0)
	 {
	 		if(ray.raydirX > 0)
	 			return (TEX_WE);
	 		else
	 			return (TEX_EA);
	}
	else
	{
		if (ray.raydirY > 0)
	 			return (TEX_NO);
	 		else
	 			return (TEX_SO);
	}
}

void	render(t_game *game)
{
	t_ray	ray;
	int		i;
	int		direction;

	i = -1;
	initialize_ray(&ray);
	while (++i < WIN_W)
	{
		ray = init_ray(game, i);
		dda_analysis(game, &ray);
		direction = get_wall_direction(ray);
		draw_column(&ray, i, game, game->wall_tex[direction]);
	}
}
