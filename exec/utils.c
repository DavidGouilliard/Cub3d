/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:42:27 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:18:22 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	free_map(game->map, game->map_height);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	while (i < TEX_TOTAL)
	{
		if (game->tex_path[i])
			free(game->tex_path[i]);
		if (game->wall_tex[i].img)
			mlx_destroy_image(game->mlx_ptr, game->wall_tex[i++].img);
	}
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

void	error_exit(char *str, t_game *game)
{
	free_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] && i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
