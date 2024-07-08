/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:28:36 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/08 20:34:54 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	angle_reset(double angle)
{
	if (angle > M_PI * 2)
		return (angle -= M_PI * 2);
	if (angle < 0)
		return angle += M_PI * 2;
	else
		return (angle);
}

void	player_controller(t_game *game)
{
	if (game->player.rotate == 1)
		game->player.angle += 0.001 * ROTSPEED;
	else if (game->player.rotate == -1)
		game->player.angle -= 0.001 * ROTSPEED;
	
	game->player.angle = angle_reset(game->player.angle);
}

void	keyrelease(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->player.ws = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->player.ws = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->player.ad = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->player.ad = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player.rotate = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player.rotate = 0;
}

void	keypress(mlx_key_data_t keydata, void *gameptr)
{
	t_game *game = (t_game *)gameptr;
	
	// if (keydata.key == MLX_KEY_ESCAPE)
		// salir
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player.ws = 1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->player.ws = -1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->player.ad = 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->player.ad = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player.rotate = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player.rotate = -1;
	keyrelease(keydata, game);
}