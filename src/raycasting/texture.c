/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:48:22 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/20 16:01:20 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

double	get_x_o(t_game *game, int t_width)
{
	double	x_o;

	if (game->ray.type == HORIZONTAL)
		x_o = (int)fmodf((game->ray.x_h * (t_width / TILESIZE)), t_width);
	else
		x_o = (int)fmodf((game->ray.y_v * (t_width / TILESIZE)), t_width);
	return (x_o);
}

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
