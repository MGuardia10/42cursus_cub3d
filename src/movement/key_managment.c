/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:36:28 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/20 16:06:05 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	t_game	*game;

	game = (t_game *)gameptr;
	if (keydata.key == MLX_KEY_ESCAPE)
		terminate_game(game);
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
