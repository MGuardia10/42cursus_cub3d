/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:00:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/24 22:22:40 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Renders the floor and sky for a given ray in the game.
 *
 * @param game The game structure.
 * @param ray The ray index.
 * @param top_p The top pixel position.
 * @param bottom_p The bottom pixel position.
 */
void	put_floor_sky(t_game *game, int ray, int top_p, int bottom_p)
{
	int	f_color;
	int	s_color;
	int	i;

	f_color = game->map->floor.rgb;
	s_color = game->map->ceiling.rgb;
	i = 0;
	while (bottom_p < SHEIGHT)
	{
		mlx_put_pixel(game->pixel, ray, bottom_p, f_color);
		bottom_p++;
	}
	while (i < top_p)
	{
		mlx_put_pixel(game->pixel, ray, i, s_color);
		i++;
	}
}

/**
 * Renders a line on the screen using the given parameters.
 *
 * @param top_p The top position of the line.
 * @param bottom_p The bottom position of the line.
 * @param ray The ray index.
 * @param game The game structure.
 */
void	put_line(int top_p, int bottom_p, int ray, t_game *game)
{
	double			y_o;
	double			x_o;
	double			step;
	mlx_texture_t	*texture;
	uint32_t		*pixels;

	texture = get_ray_texture(game);
	pixels = (uint32_t *)texture->pixels;
	step = (double)texture->width / game->ray.wall_l;
	x_o = get_x_o(game, texture->width);
	y_o = (top_p - (SHEIGHT / 2) + (game->ray.wall_l / 2)) * step;
	if (y_o < 0)
		y_o = 0;
	put_floor_sky(game, ray, top_p, bottom_p);
	while (top_p < bottom_p)
	{
		mlx_put_pixel(game->pixel, ray, top_p, reverse_bytes(
				pixels[(int)y_o * texture->width + (int)x_o]));
		y_o += step;
		top_p++;
	}
}

/**
 * Renders a line on the screen based on the given ray.
 * 
 * @param game The game structure.
 * @param ray The index of the ray.
 */
void	render_line(t_game *game, int ray)
{
	double	line_l;
	double	top_p;
	double	bottom_p;

	game->ray.distance *= cos
		(angle_reset(game->ray.angle - game->player.angle));
	line_l = (TILESIZE / game->ray.distance) * ((SWIDTH / 2)
			/ tan(game->player.rd_fov / 2));
	bottom_p = (SHEIGHT / 2) + (line_l / 2);
	top_p = (SHEIGHT / 2) - (line_l / 2);
	game->ray.wall_l = line_l;
	if (bottom_p > SHEIGHT)
		bottom_p = SHEIGHT;
	if (top_p < 0)
		top_p = 0;
	put_line(top_p, bottom_p, ray, game);
}
