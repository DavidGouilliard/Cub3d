/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:59:07 by dagouill          #+#    #+#             */
/*   Updated: 2025/12/02 14:23:43 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		error_exit_parsing(game);
	if (!is_cub_file(av[1]))
		error_exit_parsing(game);
	if (parse(av[1], &game) != 0)
		error_exit_parsing(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "cube3D");
	if (!game->win_ptr)
		error_exit("win_ptr failed\n", game);
	init_game_img(game);
	render(game);
	game_loop(game);
	free_game(game);
	return (0);
}
