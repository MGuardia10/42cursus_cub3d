/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:48:22 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/24 20:32:42 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Reverses the byte order of an integer.
 *
 * This function takes an integer as input and reverses the byte order of the integer.
 * It performs bitwise operations to extract the individual bytes of the integer and
 * reassembles them in reverse order.
 *
 * @param c The integer to reverse the byte order of.
 * @return The integer with the byte order reversed.
 */
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

/**
 * Calculates the x-coordinate of the texture pixel to be rendered on the screen.
 * 
 * @param game The game struct containing the ray and tile information.
 * @param t_width The width of the texture.
 * @return The x-coordinate of the texture pixel.
 */
double	get_x_o(t_game *game, int t_width)
{
	double	x_o;

	if (game->ray.type == HORIZONTAL)
		x_o = (int)fmodf((game->ray.x_h * (t_width / TILESIZE)), t_width);
	else
		x_o = (int)fmodf((game->ray.y_v * (t_width / TILESIZE)), t_width);
	return (x_o);
}

/**
 * Retrieves the appropriate texture based on the ray angle and type.
 * 
 * @param game The game structure containing the ray and map information.
 * @return A pointer to the mlx_texture_t structure representing the texture.
 */
mlx_texture_t	*get_ray_texture(t_game *game)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (game->ray.angle > M_PI && game->ray.angle < 2 * M_PI
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.north_tx;
	else if (game->ray.angle < M_PI && game->ray.angle > 0
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.south_tx;
	else if (game->ray.angle < 3 * M_PI / 2 && game->ray.angle > M_PI / 2
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.west_tx;
	else if ((game->ray.angle > 3 * M_PI / 2 || game->ray.angle < M_PI / 2)
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.east_tx;
	return (texture);
}
