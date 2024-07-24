/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:26:04 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/24 21:55:14 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Checks if a ray hits a wall in the game map.
 *
 * @param game The game struct.
 * @param x The x-coordinate of the ray.
 * @param y The y-coordinate of the ray.
 * @return Returns true if the ray hits a wall, false otherwise.
 */
bool	check_hit(t_game *game, double x, double y)
{
	unsigned int	x_m;
	unsigned int	y_m;

	if (x < 0 || y < 0)
		return (true);
	x_m = (unsigned int)floor(x / TILESIZE);
	y_m = (unsigned int)floor(y / TILESIZE);
	if ((y_m >= game->map->max_y || x_m >= game->map->x_row[y_m]))
		return (true);
	if (game->map->map_cpy[(int)y_m])
	{
		if (game->map->map_cpy[(int)y_m][(int)x_m])
		{
			if (game->map->map_cpy[(int)y_m][(int)x_m] == '1')
				return (true);
		}
	}
	return (false);
}

/**
 * Checks for intersection with walls in the game world.
 * 
 * @param game The game struct containing game data.
 * @param step Pointer to the step size for raycasting.
 * @param inter Pointer to the intersection coordinate.
 * @param o The orientation of the ray (horizontal or vertical).
 * @return -1 if there is an intersection, 1 otherwise.
 */
int	check_inter(t_game *game, double *step, double *inter, t_orientation o)
{
	if (o == HORIZONTAL)
	{
		if (game->ray.angle > 0 && game->ray.angle < M_PI)
		{
			*inter += TILESIZE;
			return (-1);
		}
		*step *= -1;
	}
	else if (o == VERTICAL)
	{
		if (!(game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2))
		{
			*inter += TILESIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

/**
 * Calculates the horizontal intersection point of a ray with the walls of the
 * game map.
 * 
 * @param game The game struct containing the player and ray information.
 * @return The distance between the player and the vertical intersection point.
 */
double	get_h_inter(t_game *game)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixel;

	y_step = TILESIZE;
	x_step = TILESIZE / tan(game->ray.angle);
	h_y = floor(game->player.y / TILESIZE) * TILESIZE;
	pixel = check_inter(game, &y_step, &h_y, HORIZONTAL);
	h_x = game->player.x + (h_y - game->player.y) / tan(game->ray.angle);
	if ((game->ray.angle > M_PI / 2 && game->ray.angle < (3 * M_PI) / 2)
		&& x_step > 0)
		x_step *= -1;
	else if ((game->ray.angle > (3 * M_PI) / 2 || game->ray.angle < M_PI / 2)
		&& x_step < 0)
		x_step *= -1;
	while (!check_hit(game, h_x, h_y - pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray.x_h = h_x;
	game->ray.y_h = h_y;
	return (sqrt(pow(h_x - game->player.x, 2) + pow(h_y - game->player.y, 2)));
}

/**
 * Calculates the vertical intersection point of a ray with the walls of the
 * game map.
 * 
 * @param game The game struct containing the player and ray information.
 * @return The distance between the player and the vertical intersection point.
 */
double	get_v_inter(t_game *game)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;

	x_step = TILESIZE;
	y_step = TILESIZE * tan(game->ray.angle);
	v_x = floor(game->player.x / TILESIZE) * TILESIZE;
	pixel = check_inter(game, &x_step, &v_x, VERTICAL);
	v_y = game->player.y + (v_x - game->player.x) * tan(game->ray.angle);
	if ((game->ray.angle > M_PI && game->ray.angle < 2 * M_PI) && y_step > 0)
		y_step *= -1;
	else if ((game->ray.angle < M_PI && game->ray.angle > 0) && y_step < 0)
		y_step *= -1;
	while (!check_hit(game, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray.x_v = v_x;
	game->ray.y_v = v_y;
	return (sqrt(pow(v_x - game->player.x, 2) + pow(v_y - game->player.y, 2)));
}

/**
 * Casts rays to render the game scene.
 *
 * This function casts rays from the player's perspective to render the game
 * scene. It calculates the intersection points with walls and determines the
 * distance to each intersection. The function then calls the render_line
 * function to draw the corresponding line on the screen.
 *
 * @param game A pointer to the game structure.
 */
void	castrays(t_game *game)
{
	int		ray;
	double	h_inter;
	double	v_inter;

	ray = 0;
	game->ray.angle = game->player.angle - (game->player.rd_fov / 2);
	while (ray < SWIDTH)
	{
		game->ray.angle = angle_reset(game->ray.angle);
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		if (v_inter <= h_inter)
		{
			game->ray.distance = v_inter;
			game->ray.type = VERTICAL;
		}
		else
		{
			game->ray.distance = h_inter;
			game->ray.type = HORIZONTAL;
		}
		render_line(game, ray);
		ray++;
		game->ray.angle += (game->player.rd_fov / SWIDTH);
	}
}
