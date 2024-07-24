/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:52:58 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/24 22:50:10 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Draws a square on the minimap.
 *
 * @param game   The game struct.
 * @param map_x  The x-coordinate of the square on the map.
 * @param map_y  The y-coordinate of the square on the map.
 * @param color  The color of the square.
 */
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

/**
 * Draws the player on the minimap.
 * 
 * @param game The game struct.
 */
void	draw_player(t_game *game)
{
	int			p_x;
	int			p_y;
	int			color;
	uint32_t	i;
	uint32_t	j;

	color = MMAP_PLAYER;
	p_x = floor((game->player.x / TILESIZE) * (
				game->map->map_img->height / game->map->max_y));
	p_y = floor((game->player.y / TILESIZE) * (
				game->map->map_img->height / game->map->max_y));
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

/**
 * Renders the minimap based on the game's map data.
 * 
 * @param game The game instance.
 */
void	render_minimap(t_game *game)
{
	int	map_x;
	int	map_y;
	int	color;

	map_y = 0;
	while (game->map->map_cpy[map_y])
	{
		map_x = 0;
		while (game->map->map_cpy[map_y][map_x])
		{
			if (game->map->map_cpy[map_y][map_x] == '1')
				color = MMAP_WALL;
			else if (game->map->map_cpy[map_y][map_x] == ' ')
				color = TRANSPARENT;
			else
				color = MMAP_SPACE;
			draw_square(game, map_x, map_y, color);
			map_x++;
		}
		map_y++;
	}
	draw_player(game);
}
