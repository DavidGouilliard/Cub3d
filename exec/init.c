/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:17:00 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 20:18:45 by dagouill         ###   ########.fr       */
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
        &game->img.endian
    );
}

void load_textures(t_game *game)
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
	game->win_ptr = NULL;
	game->frames = 0;
	game->fps = 0;
	game->current_time = get_time();
	game->last_time = game->current_time;
	game->fps_last_time = game->current_time;
	game->map = state.map_lines;
	game->map_height = state.map_height;
	game->colors[0] = (state.ceiling.r << 16) + (state.ceiling.g << 8) + state.ceiling.b;
	game->colors[1] = (state.floor.r << 16) + (state.floor.g << 8) + state.floor.b;
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

/*void	init_map(char *file, t_game *game)*/
/*{*/
/*	int		fd;*/
/*	t_list	*line;*/
/*	char	*raw_line;*/
/**/
/*	game->map_list = NULL;*/
/*	fd = open(file, O_RDONLY, 0777);*/
/*	if (fd < 0)*/
/*		error_exit("error map open\n", game);*/
/*	while (1)*/
/*	{*/
/*		raw_line = get_next_line(fd);*/
/*		if (raw_line == NULL)*/
/*			break ;*/
/*		line = ft_lstnew((void *)raw_line);*/
/*		if (line == NULL)*/
/*		{*/
/*			free(raw_line);*/
/*			close(fd);*/
/*			error_exit("malloc error\n", game);*/
/*		}*/
/*		ft_lstadd_back(&(game->map_list), line);*/
/*		game->height++;*/
/*	}*/
/*	init_array(game);*/
/*	close(fd);*/
/*}*/
/**/
/*void	init_array(t_game *game)*/
/*{*/
/*	int		i;*/
/*	int		len;*/
/*	t_list	*p;*/
/*	char	*line;*/
/**/
/*	i = 0;*/
/*	p = game->map_list;*/
/*	game->map = (char **) malloc(sizeof(char *) * (game->height + 1));*/
/*	if (game->map == NULL)*/
/*		error_exit("malloc error\n", game);*/
/*	while (p)*/
/*	{*/
/*		line = (char *) p->content;*/
/*		len = ft_strlen(line);*/
/*		if (len > 0 && line[len - 1] == '\n')*/
/*			line[len - 1] = '\0';*/
/*		game->map[i] = ft_strdup(line);*/
/*		if (game->map[i] == NULL)*/
/*			error_exit("malloc error\n", game);*/
/*		i++;*/
/*		p = p->next;*/
/*	}*/
/*	game->map[i] = NULL;*/
/*	ft_lstclear(&(game->map_list), free);*/
/*}*/

void	init_player(t_game *g, t_parser_state state)
{
	g->player.x = (double) state.player_x + 0.5;
	g->player.y = (double) state.player_y + 0.5;
	/*g->player.dir_x = 0;*/
	/*g->player.dir_y = 0;*/
	/*direction = get_player_pos(g);*/
	set_player_dir(g, state.player_dir);
	g->player.plane_x = -g->player.dir_y * FOV;
	g->player.plane_y = g->player.dir_x * FOV;
	g->player.move_speed = MOVE_SPEED;
	g->player.cos_rot = cos(ROT_SPEED);
	g->player.sin_rot = sin(ROT_SPEED);
}
