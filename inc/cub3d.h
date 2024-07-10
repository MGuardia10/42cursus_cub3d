/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:54:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/10 14:36:46 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include <math.h>
# include <errno.h>

/******************************************************************************
*	Typedefs
******************************************************************************/

typedef struct s_color			t_color;
typedef struct s_texture		t_texture;
typedef struct s_map			t_map;
typedef struct s_player			t_player;
typedef struct s_game			t_game;
typedef struct s_mlx			t_mlx;

typedef enum e_valid_chars		t_valid_chars;

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

/******************************************************************************
*	Structs
******************************************************************************/

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

	/* map array */
	char			**map_cpy;
	unsigned int	max_y;
	unsigned int	max_x;
};

struct s_player
{
	t_valid_chars	orientation;
	int				x;
	int				y;
};

struct s_mlx
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

struct	s_game
{
	/* MAP */
	t_map			*map;

	/* PLAYER */
	t_player		player;

	/* MLX */
	t_mlx			mlx;
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

#endif