/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:42:27 by dagouill          #+#    #+#             */
/*   Updated: 2025/12/02 14:18:53 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_textures(t_game *game, int has_mlx)
{
	int	i;

	i = 0;
	while (i < TEX_TOTAL)
	{
		if (game->tex_path[i])
			free(game->tex_path[i]);
		if (has_mlx && game->wall_tex[i].img)
			mlx_destroy_image(game->mlx_ptr, game->wall_tex[i].img);
		i++;
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game->map, game->map_height);
	if (game->mlx_ptr)
	{
		if (game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		if (game->img.img)
			mlx_destroy_image(game->mlx_ptr, game->img.img);
		free_textures(game, 1);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	else
		free_textures(game, 0);
	free(game);
}

void	error_exit(char *str, t_game *game)
{
	free_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

void	error_exit_parsing(t_game *game)
{
	free_game(game);
	exit(1);
}

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < size && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
