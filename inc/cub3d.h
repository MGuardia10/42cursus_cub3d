/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:54:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 17:23:33 by raalonso         ###   ########.fr       */
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
# define ROTSPEED 10
# define MOVESPEED 1

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
	/* Path to map */
	char			*file;

	/* Textures of the map */
	t_texture		textures;

	/* floor and ceiling colors */
	t_color			floor;
	t_color			ceiling;

	/* map array */
	char			**map_cpy;
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
	t_map			map;

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
void	cpy_map(t_map *map, char **arr, int i);
void	error(char *error, bool flag, char *pstr);
void	item_error(char *item, char *error);
bool	is_empty(char *str);
bool	is_texture(char *str);
bool	is_color(char *str);
int		get_color(t_color item);

/* RAYCASTING */
void	init_window(t_game *game);
void	castrays(t_game *game);
double	get_v_inter(t_game *game);
double	get_h_inter(t_game *game);
int		check_inter(t_game *game, double *step, double *inter, t_orientation o);
bool	check_hit(t_game *game, double x, double y);
void	render_line(t_game *game, int ray);
void	put_line(int t_pixel, int b_pixel, int ray, t_game *game);

/* MOVEMENT */
void	keypress(mlx_key_data_t keydata, void *gameptr);
void	keyrelease(mlx_key_data_t keydata, t_game *game);
void	player_controller(t_game *game);
double	angle_reset(double angle);

#endif