/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:28:36 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/22 18:54:10 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function `angle_reset` updates the angle value.
 * 
 * @param angle the current value of the angle in a double data type.
 */
double	angle_reset(double angle)
{
	if (angle > M_PI * 2)
		return (angle -= M_PI * 2);
	if (angle < 0)
		return (angle += M_PI * 2);
	else
		return (angle);
}

/**
 * The function `check_move` updates the player's position in a game based on
 * specified new coordinates, while ensuring the player stays within the game
 * map boundaries and only moves to valid positions on the map.
 * 
 * @param new_x the new x-coordinate where the player will move to.
 * @param new_y the new y-coordinate to which the player will move.
 * @param game a pointer to a structure of type `t_game`.
 */
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

/**
 * The function `move_player` updates the player's position based on movement
 * input and angle in a game.
 * 
 * @param game a pointer to a structure of type `t_game`.
 * @param new_x the new x-coordinate where the player will move to.
 * @param new_y the new y-coordinate to which the player will move.
 */
void	move_player(t_game *game, double new_x, double new_y)
{
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

/**
 * The player_controller function updates the player's angle and movement based
 * on input.
 * 
 * @param game a pointer to a structure of type `t_game`, which contains
 * information about the game state, including the player's position, rotation
 * status, movement status, and other relevant data.
 */
void	player_controller(t_game *game)
{
	if (game->player.rotate == 1)
		game->player.angle += 0.001 * ROTSPEED;
	else if (game->player.rotate == -1)
		game->player.angle -= 0.001 * ROTSPEED;
	if (game->player.ws != 0 || game->player.ad != 0)
		move_player(game, 0, 0);
	game->player.angle = angle_reset(game->player.angle);
}
