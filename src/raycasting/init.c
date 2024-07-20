/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:22:45 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/20 14:26:27 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(t_game *game, int map_x, int map_y, int color)
{
	int			s_x;
	int			s_y;
	uint32_t	i;
	uint32_t	j;

	s_x = map_x * (game->map->map_img->height / game->map->max_y);
	s_y = map_y * (game->map->map_img->height / game->map->max_y);
	i = 0;
	while (i < game->map->map_img->height / game->map->max_y)
	{
		j = 0;
		while (j < game->map->map_img->height / game->map->max_y)
		{
			mlx_put_pixel(game->map->map_img, s_x + j, s_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	p_x;
	int	p_y;
	uint32_t	i;
	uint32_t	j;
	int		color = 0xCAE8FF;

	p_x = floor((game->player.x / TILESIZE) * (game->map->map_img->height / game->map->max_y));
	p_y = floor((game->player.y / TILESIZE) * (game->map->map_img->height / game->map->max_y));
	p_x -= (game->map->map_img->height / game->map->max_y) / 2;
	p_y -= (game->map->map_img->height / game->map->max_y) / 2;
	i = 0;
	while (i < game->map->map_img->height / game->map->max_y)
	{
		j = 0;
		while (j < game->map->map_img->height / game->map->max_y)
		{
			mlx_put_pixel(game->map->map_img, p_x + j, p_y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int map_x;
	int map_y;
	int color;

	map_y = 0;
	while (game->map->map_cpy[map_y])
	{
		map_x = 0;
		while (game->map->map_cpy[map_y][map_x])
		{
			if (game->map->map_cpy[map_y][map_x] == '1')
				color = game->map->ceiling.rgb + 1500;
			else if (game->map->map_cpy[map_y][map_x] == ' ')
				color = 0x00000000;
			else
				color = 0xFFFFFFFF;
			draw_square(game, map_x, map_y, color);
			map_x++;
		}
		map_y++;
	}
	draw_player(game);
}

void	game_loop(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	castrays(game);
	player_controller(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		render_minimap(game);
}

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
	mlx_image_to_window(game->mlx, game->map->map_img, SWIDTH / 20, SHEIGHT / 20);
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
	game->pixel = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	mlx_image_to_window(game->mlx, game->pixel, 0, 0);
	init_player(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		init_minimap(game);
	init_textures(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &keypress, game);
	mlx_loop(game->mlx);
}
