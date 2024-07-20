/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:00:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/20 15:10:15 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

double	get_x_o(t_game *game, int t_width)
{
	double	x_o;

	if (game->ray.type == HORIZONTAL)
		x_o = (int)fmodf((game->ray.x_h * (t_width / TILESIZE)), t_width);
	else
	{
		x_o = (int)fmodf((game->ray.y_v * (t_width / TILESIZE)), t_width);
	}
	return (x_o);
}

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

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SWIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SHEIGHT)
		return ;
	mlx_put_pixel(game->pixel, x, y, color);
}

void	put_line(int top_p, int bottom_p, int ray, t_game *game)
{
	double		y_o;
	double		x_o;
	double		step;
	mlx_texture_t	*texture;
	uint32_t	*pixels;
	
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
		my_mlx_pixel_put(game, ray, top_p, reverse_bytes(pixels[(int)y_o * texture->width + (int)x_o]));
		y_o += step;
		top_p++;
	}
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

void	render_line(t_game *game, int ray)
{
	double	line_l;
	double	top_p;
	double	bottom_p;

	game->ray.distance *= cos(angle_reset(game->ray.angle - game->player.angle));
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
