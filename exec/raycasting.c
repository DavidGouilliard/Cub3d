/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:05:39 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:43:12 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_ray(t_ray *ray)
{
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->horizontalwall = 0;
	ray->raydirx = 0;
	ray->raydiry = 0;
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->camerax = 0;
	ray->walldist = 0;
	ray->wall_x = 0;
}

void	ray_directions(t_game *game, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - game->player.x) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - game->player.y) * ray->deltadisty;
	}
}

void	dda_step(t_ray *ray)
{
	if (ray->sidedistx < ray->sidedisty)
	{
		ray->sidedistx += ray->deltadistx;
		ray->mapx += ray->stepx;
		ray->horizontalwall = 0;
	}
	else
	{
		ray->sidedisty += ray->deltadisty;
		ray->mapy += ray->stepy;
		ray->horizontalwall = 1;
	}
}

void	dda_analysis(t_game *game, t_ray *ray)
{
	while (1)
	{
		dda_step(ray);
		if (ray->mapx < 0 || ray->mapy < 0)
		{
			ray->walldist = 1e30;
			return ;
		}
		if (game->map[ray->mapy][ray->mapx] == '1')
			break ;
	}
	if (ray->horizontalwall == 0)
	{
		ray->walldist = (ray->mapx - game->player.x
				+ (1 - ray->stepx) / 2) / ray->raydirx;
		ray->wall_x = game->player.y + ray->walldist * ray->raydiry;
	}
	else
	{
		ray->walldist = (ray->mapy - game->player.y
				+ (1 - ray->stepy) / 2) / ray->raydiry;
		ray->wall_x = game->player.x + ray->walldist * ray->raydirx;
	}
}

t_ray	init_ray(t_game *game, int x)
{
	t_ray	ray;

	ray.camerax = 2 * x / (double)WIN_W - 1;
	ray.raydirx = game->player.dir_x + game->player.plane_x * ray.camerax;
	ray.raydiry = game->player.dir_y + game->player.plane_y * ray.camerax;
	ray.mapx = (int)game->player.x;
	ray.mapy = (int)game->player.y;
	if (ray.raydirx == 0)
		ray.deltadistx = 1e30;
	else
		ray.deltadistx = fabs(1 / ray.raydirx);
	if (ray.raydiry == 0)
		ray.deltadisty = 1e30;
	else
		ray.deltadisty = fabs(1 / ray.raydiry);
	ray_directions(game, &ray);
	ray.horizontalwall = 0;
	ray.walldist = 0;
	return (ray);
}
