/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:00:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/10 19:48:50 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_floor_sky(t_game *game, int ray, int top_p, int bottom_p)
{
	int	f_color;
	int	s_color;
	int	i;

	f_color = game->map.floor.rgb;
	s_color = game->map.ceiling.rgb;
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

void	put_line(int top_p, int bottom_p, int ray, t_game *game)
{
	int	color;

	if (game->ray.type == 1)
	{
		color = 0xFFAAAAAA;
	}
	else if (game->ray.type == 2)
	{
		color = 0xFFFAAAAA;
	}
	put_floor_sky(game, ray, top_p, bottom_p);
	while (top_p < bottom_p)
	{
		mlx_put_pixel(game->pixel, ray, top_p, color);
		top_p++;
	}
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
	if (bottom_p > SHEIGHT)
		bottom_p = SHEIGHT;
	if (top_p < 0)
		top_p = 0;

	put_line(top_p, bottom_p, ray, game);
}
