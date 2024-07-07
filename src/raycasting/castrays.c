/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:26:04 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/07 19:59:10 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	check_hit(t_game *game, double x, double y)
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (true);
	x_m = floor (x / TILESIZE);
	y_m = floor (y / TILESIZE);
	if ((y_m >= 14 || x_m >= 28))
		return (true);
	if (game->map.map_cpy[y_m][x_m] == '1')
			return (true);
	return (false);
}

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
		if (game->ray.angle > (3 * M_PI) / 2 && game->ray.angle < M_PI / 2)
		{
			*inter += TILESIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

double	get_h_inter(t_game *game)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixel;
	

	mlx_image_t *img = mlx_new_image(game->mlx, 5, 5);
	ft_memset(img->pixels, 150, img->width * img->height * sizeof(int32_t));

	y_step = TILESIZE;
	x_step = TILESIZE / tan(game->ray.angle);


	h_y = game->player.y / TILESIZE * TILESIZE;
	pixel = check_inter(game, &y_step, &h_y, HORIZONTAL);

	h_x = game->player.x + (h_y - game->player.y) / tan(game->ray.angle);

	
	if ((game->ray.angle > M_PI / 2 && game->ray.angle < (3 * M_PI) / 2) && x_step > 0)
		x_step *= -1;
	else if ((game->ray.angle > (3 * M_PI) / 2 || game->ray.angle < M_PI / 2) && x_step < 0)
		x_step *= -1;
	
	
	while (!check_hit(game, h_x, h_y - pixel))
	{
		mlx_image_to_window(game->mlx, img, (int32_t)h_x, (int32_t)h_y);
		h_x += x_step;
		h_y += y_step;
	}
	mlx_image_to_window(game->mlx, img, game->player.x, game->player.y);
	mlx_image_to_window(game->mlx, img, (int32_t)h_x, (int32_t)h_y);
	

	return (sqrt(pow(h_x - game->player.x, 2) + pow(h_y - game->player.y, 2)));
}

double	get_v_inter(t_game *game)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;
	

	mlx_image_t *img = mlx_new_image(game->mlx, 5, 5);
	ft_memset(img->pixels, 150, img->width * img->height * sizeof(int32_t));

	x_step = TILESIZE;
	y_step = TILESIZE * tan(game->ray.angle);

	v_x = game->player.x / TILESIZE * TILESIZE;
	pixel = check_inter(game, &x_step, &v_x, VERTICAL);
	v_y = game->player.y + (v_x - game->player.x) * tan(game->ray.angle);
	
	if ((game->ray.angle > M_PI && game->ray.angle < 2 * M_PI) && x_step > 0)
		y_step *= -1;
	else if ((game->ray.angle < M_PI && game->ray.angle > 0) && x_step > 0)
		y_step *= -1;
	
	
	while (!check_hit(game, v_x - pixel, v_y))
	{
		mlx_image_to_window(game->mlx, img, (int32_t)v_x, (int32_t)v_y);
		v_x += x_step;
		v_y += y_step;
	}
	mlx_image_to_window(game->mlx, img, game->player.x, game->player.y);
	mlx_image_to_window(game->mlx, img, (int32_t)v_x, (int32_t)v_y);
	

	return (sqrt(pow(v_x - game->player.x, 2) + pow(v_y - game->player.y, 2))); // esta mal
}

void	castrays(t_game *game)
{
	int	ray;
	double h_inter;
	double v_inter;

	ray = 0;
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	game->player.rd_fov = (FOV * M_PI) / 180;
	game->player.angle = M_PI;
	printf("\nplayer angle: %f\n", game->player.angle);
	game->ray.angle = game->player.angle - (game->player.rd_fov / 2); // angulo de inicio
	while (ray < SWIDTH)
	{
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		if (h_inter <= v_inter)
			game->ray.distance = h_inter;
		else
			game->ray.distance = v_inter;
		// render wall
		ray++;
		game->ray.angle += (game->player.rd_fov / SWIDTH);
	}
}