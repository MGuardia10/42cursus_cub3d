/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:28:36 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/19 20:53:41 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	angle_reset(double angle)
{
	if (angle > M_PI * 2)
		return (angle -= M_PI * 2);
	if (angle < 0)
		return (angle += M_PI * 2);
	else
		return (angle);
}

void	check_move(double new_x, double new_y, t_game *game)
{
	long	map_x;
	long	map_y;

	map_x = ((game->player.x + new_x) / TILESIZE);
	map_y = ((game->player.y + new_y) / TILESIZE);
	if (map_y < 0 || map_x < 0)
		return ;
	if (map_y > game->map->max_y || map_x > game->map->max_x)
		return ;
	if (game->map->map_cpy[map_y][map_x] == '0'
		|| game->map->map_cpy[map_y][map_x] == (char)game->player.orientation)
	{
		game->player.x += new_x;
		game->player.y += new_y;
	}
}

void	move_player(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (game->player.ws == 1)
	{
		new_x = cos(game->player.angle) * MOVESPEED;
		new_y = sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ws == -1)
	{
		new_x = -cos(game->player.angle) * MOVESPEED;
		new_y = -sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == 1)
	{
		new_x = -sin(game->player.angle) * MOVESPEED;
		new_y = cos(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == -1)
	{
		new_x = sin(game->player.angle) * MOVESPEED;
		new_y = -cos(game->player.angle) * MOVESPEED;
	}
	check_move(new_x, new_y, game);
}

void	player_controller(t_game *game)
{
	if (game->player.rotate == 1)
		game->player.angle += 0.001 * ROTSPEED;
	else if (game->player.rotate == -1)
		game->player.angle -= 0.001 * ROTSPEED;
	if (game->player.ws != 0 || game->player.ad != 0)
		move_player(game);
	game->player.angle = angle_reset(game->player.angle);
}
