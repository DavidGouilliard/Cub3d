/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:31:50 by dagouill          #+#    #+#             */
/*   Updated: 2025/11/23 09:47:25 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

#define CUB3D_H


# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "stdlib.h"
# include "sys/time.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "parser/parser.h"
# include "parser/parse_header/parse_header_internal.h"
# include "parser/parse_map/parse_map_internal.h"

# define WIN_W 1920
# define WIN_H 1080
# define FOV 0.66
# define MOVE_SPEED 3.0
# define ROT_SPEED 3.0
# define MOUSE_SPEED 0.003

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_line
{
	double	wallheight;
	int 	x;
	int 	y;
	int 	drawstart;
	int 	drawend;
	int 	tex_x;
	int 	tex_y;
	int 	tex_step;
	int 	tex_pos;
}	t_line;

typedef struct s_tex
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_tex;

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		horizontalwall;
	double	raydirX;
	double	raydirY;
	double	deltadistX;
	double	deltadistY;
	double	sidedistX;
	double	sidedistY;
	double	cameraX;
	double	walldist;
	double	wall_x;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	cos_rot;
	double	sin_rot;
}	t_player;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	r_left;
	int	r_right;
}	t_key;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			frames;
	double		last_time;
	double		fps_last_time;
	double		current_time;
	double		frame_time;
	double		fps;
	t_list		*map_list;
	t_data		img;
	t_tex		wall_tex[TEX_TOTAL];
	t_player	player;
	char		*tex_path[TEX_TOTAL];
	char		**map;
	int			colors[2];
	int			map_height;
	t_key		keys;
}	t_game;
//Game loop
int		on_keypress(int keycode, t_game *game);
int		on_destroy(t_game *game);
void	game_loop(t_game *game);
void	free_game(t_game *game);
//Init
void	init_game_img(t_game *game);
t_game	*init_game(t_parser_state state);
void	init_map(char *file, t_game *game);
void	init_array(t_game *game);
void	init_player(t_game *g, t_parser_state state);
//Player move
void	move_up(double new_x, double new_y, t_game *game);
void	move_down(double new_x, double new_y, t_game *game);
void	move_left(double new_x, double new_y, t_game *game);
void	move_right(double new_x, double new_y, t_game *game);
void	straight_move(int keycode, t_game *game);
void	rotate_player(t_player *player, int direction);
void	move_player(int keycode, t_game *game);
void	set_player_dir(t_game *g, char C);
char	get_player_pos(t_game *g);
//Raycasting
void	initialize_ray(t_ray *ray);
void	ray_directions(t_game *game, t_ray *ray);
void	dda_analysis(t_game *game, t_ray *ray);
t_ray	init_ray(t_game *game, int x);
//Rendering
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_column(t_ray *ray, int x, t_game *game, t_tex tex);
void	render(t_game *game);
//Utils
void	error_exit(char *str, t_game *game);
void	free_map(char **map, int size);
//Debug functions
/*void	print_map(t_game *game);*/
/*void	print_player(t_game *game);*/
double	get_time(void);
void	display_fps(t_game *game);
void	update_fps(t_game *game);
#endif
