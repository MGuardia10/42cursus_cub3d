/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:36:28 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/22 18:47:56 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function `keyrelease` updates the movement and rotation status of the
 * player in a game based on key release events.
 * 
 * @param keydata a struct or data type that contains information about a key
 * event.
 * @param game a pointer to a structure of type `t_game`.
 */
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

/**
 * The keypress function handles key events for a game, setting player movement
 * and rotation based on the pressed keys.
 * 
 * @param keydata a struct or data type that contains information about a key
 * event. 
 * @param gameptr a void pointer that is used to pass a pointer to a `t_game`
 * structure.
 */
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
