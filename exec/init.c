/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:17:00 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/29 01:36:21 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx_ptr, WIN_W, WIN_H);
			game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
}

void	load_textures(t_game *game)
{
	int		i;
	t_tex	*tex;

	i = 0;
	while (i < TEX_TOTAL)
	{
		tex = &game->wall_tex[i];
		tex->img = mlx_xpm_file_to_image(
				game->mlx_ptr, game->tex_path[i], &tex->width,
				&tex->height);
		if (!tex->img)
			error_exit("Failed to load wall texture\n", game);
		tex->addr = mlx_get_data_addr(tex->img,
				&tex->bits_per_pixel, &tex->line_length,
				&tex->endian);
		i++;
	}
}

void	init_keys(t_game *game)
{
		game->keys.up = 0;
		game->keys.down = 0;
		game->keys.left = 0;
		game->keys.right = 0;
		game->keys.r_left = 0;
		game->keys.r_right = 0;
}

void	norminette_for_init(t_game *game, t_parser_state state)
{
	game->win_ptr = NULL;
	game->frames = 0;
	game->fps = 0;
	game->current_time = get_time();
	game->last_time = game->current_time;
	game->fps_last_time = game->current_time;
	game->map = state.map_lines;
	game->map_height = state.map_height;
	game->colors[0] = (state.ceiling.r << 16)
		+ (state.ceiling.g << 8) + state.ceiling.b;
	game->colors[1] = (state.floor.r << 16)
		+ (state.floor.g << 8) + state.floor.b;
}

t_game	*init_game(t_parser_state state)
{
	t_game	*game;
	int		i;

	i = 0;
	game = (t_game *) malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = NULL;
	init_keys(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_exit("error mlx ptr\n", game);
	norminette_for_init(game, state);
	while (i < TEX_TOTAL)
	{
		game->wall_tex[i].img = NULL;
		game->tex_path[i] = state.tex_path[i];
		i++;
	}
	init_player(game, state);
	load_textures(game);
	return (game);
}
