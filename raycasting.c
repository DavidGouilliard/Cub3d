/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:05:39 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 20:07:21 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_ray(t_ray *ray)
{
	ray->mapX = 0;
	ray->mapY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->horizontalwall = 0;
	ray->raydirX = 0;
	ray->raydirY = 0;
	ray->deltadistX = 0;
	ray->deltadistY = 0;
	ray->sidedistX = 0;
	ray->sidedistY = 0;
	ray->cameraX = 0;
	ray->walldist = 0;
}

void	ray_directions(t_game *game, t_ray *ray)
{
	if (ray->raydirX < 0)
	{
		ray->stepX = -1;
		ray->sidedistX = (game->player.x - ray->mapX) * ray->deltadistX;
	}
	else	
	{
		ray->stepX = 1;
		ray->sidedistX = (ray->mapX + 1 - game->player.x) * ray->deltadistX;
	}
	if (ray->raydirY < 0)
	{
		ray->stepY = -1;
		ray->sidedistY = (game->player.y - ray->mapY) * ray->deltadistY;
	}
	else	
	{
		ray->stepY = 1;
		ray->sidedistY = (ray->mapY + 1 - game->player.y) * ray->deltadistY;
	}
}

void	dda_analysis(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedistX < ray->sidedistY)
		{
			ray->sidedistX += ray->deltadistX;
			ray->mapX += ray->stepX;
			ray->horizontalwall = 0;
		}
		else
		{
			ray->sidedistY += ray->deltadistY;
			ray->mapY += ray->stepY;
			ray->horizontalwall = 1;
		}
		if (game->map[ray->mapY][ray->mapX] == '1')
			break;
	}
	if (ray->horizontalwall == 0)
        ray->walldist = (ray->mapX - game->player.x + (1 - ray->stepX) / 2) / ray->raydirX;
    else
        ray->walldist = (ray->mapY - game->player.y + (1 - ray->stepY) / 2) / ray->raydirY;
}

t_ray	init_ray(t_game *game, int x)
{
	t_ray	ray;

	ray.cameraX = 2 * x / (double)WIN_W - 1;
	ray.raydirX = game->player.dir_x + game->player.plane_x * ray.cameraX;
	ray.raydirY = game->player.dir_y + game->player.plane_y * ray.cameraX;
	ray.mapX = (int)game->player.x;
	ray.mapY = (int)game->player.y;
	if (ray.raydirX == 0)
		ray.deltadistX = 1e30;
	else
		ray.deltadistX = fabs(1/ray.raydirX);
	if (ray.raydirY == 0)
		ray.deltadistY = 1e30;
	else
		ray.deltadistY = fabs(1/ray.raydirY);
	ray_directions(game, &ray);
	ray.horizontalwall = 0;
	ray.walldist = 0;
	return (ray);
}
