/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:54:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/13 10:52:13 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
#include "../mlx/include/MLX42/MLX42.h"
# include <math.h>
# include <errno.h>

/******************************************************************************
*	Defines
******************************************************************************/

# define SHEIGHT 800
# define SWIDTH 1200
# define TILESIZE 40
# define FOV 60
# define ROTSPEED 25
# define MOVESPEED 3

/******************************************************************************
*	Typedefs
******************************************************************************/

typedef struct s_ray			t_ray;
typedef struct s_color			t_color;
typedef struct s_texture		t_texture;
typedef struct s_map			t_map;
typedef struct s_player			t_player;
typedef struct s_game			t_game;

typedef enum e_valid_chars		t_valid_chars;
typedef enum e_orientation		t_orientation;

/******************************************************************************
*	Enums
******************************************************************************/

enum	e_valid_chars
{
	EMPTY = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E'
};

enum	e_orientation
{
	HORIZONTAL,
	VERTICAL
};

/******************************************************************************
*	Structs
******************************************************************************/

struct s_ray
{
	double	angle;
	double	distance;
	int		type;
};

struct s_color
{
	int				rgb;
	int				r;
	int				g;
	int				b;
};

struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
};

struct s_map
{
	/* Map file */
	char			*file;
	char			**file_arr;
	char			**item_line;

	/* Textures of the map */
	t_texture		textures;

	/* floor and ceiling colors */
	t_color			floor;
	t_color			ceiling;
	int				*color_arr;

	/* map array */
	char			**map_cpy;
	unsigned int	max_y;
	unsigned int	max_x;

	/* minimapmap rendering */
	mlx_image_t		*map_img;
};

struct s_player
{
	t_valid_chars	orientation;
	double			angle;
	double			rd_fov; // en radianes
	double				x;
	double				y;
	int					ws; // para mover jugador
	int					ad; // para mover jugador
	int					rotate; // rotar jugador
};

struct	s_game
{
	/* MAP */
	t_map			*map;

	/* PLAYER */
	t_player		player;

	/* MLX */
	mlx_t			*mlx;
	mlx_image_t		*pixel;
	
	/* RAYCASTING */
	t_ray			ray;
};

/******************************************************************************
*	FUNCTION PROTOTYPES
******************************************************************************/

/* PARSING */
void	init_game(t_game *game, int argc, char **argv);
void	manage_textures(t_game *game, char **line);
void	manage_colors(t_game *game, char **line);
bool	has_invalid_chars(char *str);
int		find_player(t_player *player, char *str, int j);
char	**cpy_map(char **arr, int i);
bool	valid_map_limits(t_game *game, t_map *map);
bool	empty_found(char **map, int *x, int *y);
int		flood_fill(char **map, int x, int y);
void	error(t_game *game, char *error, bool flag, char *pstr);
void	item_error(t_game *game, char *item, char *error);
bool	is_empty(char *str);
bool	is_texture(char *str);
bool	is_color(char *str);
int		get_color(t_color item);
void	clean_game(t_game *game);
void    terminate_game(void *gameptr);

/* RAYCASTING */
void	init_window(t_game *game);
void	init_player(t_game *game);
double	get_p_angle(t_game *game);
void	game_loop(void *gameptr);
void	castrays(t_game *game);
double	get_v_inter(t_game *game);
double	get_h_inter(t_game *game);
int		check_inter(t_game *game, double *step, double *inter, t_orientation o);
bool	check_hit(t_game *game, double x, double y);
void	render_line(t_game *game, int ray);
void	put_line(int t_pixel, int b_pixel, int ray, t_game *game);
void	put_floor_sky(t_game *game, int ray, int top_p, int bottom_p);

/* MOVEMENT */
void	keypress(mlx_key_data_t keydata, void *gameptr);
void	keyrelease(mlx_key_data_t keydata, t_game *game);
void	player_controller(t_game *game);
double	angle_reset(double angle);
void	check_move(double new_x, double new_y, t_game *game);
void	move_player(t_game *game);

#endif