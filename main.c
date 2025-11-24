/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:59:07 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 10:56:50 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		error_exit("wrong argument count\n", game);
	game = initialize_struct(av[1]);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (free(game), 1);
	/*print_map(game);*/
	/*print_player(game);*/
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "Cube3d");
	if (!game->win_ptr)
		error_exit("win_ptr failed\n", game);
	init_game_img(game);
	render(game);
	game_loop(game);
	free_game(game);
	return (0);
}
