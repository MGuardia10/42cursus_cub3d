/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:54:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/12 13:20:33 by mguardia         ###   ########.fr       */
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
typedef struct s_cub3d			t_cub3d;

typedef enum e_orientation		t_orientation;

/******************************************************************************
*	Enums
******************************************************************************/

enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST
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
	t_orientation	orientation;
	int				x;
	int				y;
};

struct	s_cub3d
{
	/* MAP */
	t_map			map;

	/* PLAYER */
	t_player		player;

	/* MLX */
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

/******************************************************************************
*	FUNCTION PROTOTYPES
******************************************************************************/

/* PARSING */
int	args_parsing(int argc, char **argv);

#endif