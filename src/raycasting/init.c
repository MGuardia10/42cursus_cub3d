/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:22:45 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/20 16:00:25 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_p_angle(t_game *game)
{
	if (game->player.orientation == NORTH)
		return (3 * M_PI / 2);
	else if (game->player.orientation == SOUTH)
		return (M_PI / 2);
	else if (game->player.orientation == WEST)
		return (M_PI);
	else if (game->player.orientation == EAST)
		return (0);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	game->player.rd_fov = (FOV * M_PI) / 180;
	game->player.angle = get_p_angle(game);
	game->player.ws = 0;
	game->player.ad = 0;
}

void	init_minimap(t_game *game)
{
	int	m_w;
	int	m_h;

	m_w = floor(game->map->max_x * (SWIDTH / 100));
	m_h = floor(game->map->max_y * (SHEIGHT / 100));
	game->map->map_img = mlx_new_image(game->mlx, m_w, m_h);
	mlx_image_to_window(game->mlx, game->map->map_img, SWIDTH / 20,
		SHEIGHT / 20);
}

void	init_textures(t_game *game)
{
	game->map->textures.east_tx = mlx_load_png(game->map->textures.east);
	game->map->textures.north_tx = mlx_load_png(game->map->textures.north);
	game->map->textures.south_tx = mlx_load_png(game->map->textures.south);
	game->map->textures.west_tx = mlx_load_png(game->map->textures.west);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(SWIDTH, SHEIGHT, "cub3d", false);
	if (!game->mlx)
		error(game, NULL, true, "malloc");
	game->pixel = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	if (!game->pixel)
	{
		mlx_close_window(game->mlx);
		error(game, NULL, true, "malloc");
	}
	if (mlx_image_to_window(game->mlx, game->pixel, 0, 0) < 0)
	{
		mlx_close_window(game->mlx);
		error(game, NULL, true, "malloc");
	}
	init_player(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		init_minimap(game);
	init_textures(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &keypress, game);
	mlx_close_hook(game->mlx, &terminate_game, game);
	mlx_loop(game->mlx);
}
