/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/22 18:44:40 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * The function `game_loop` takes a pointer to a game structure, casts rays,
 * controls the player and renders a minimap.
 * 
 * @param gameptr The `gameptr` parameter is a void pointer that is passed to
 * `game_loop` function. It is then cast to a pointer of type `t_game` using
 * `(t_game *)gameptr` within the function to access the game data structure.
 */
void	game_loop(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	castrays(game);
	player_controller(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		render_minimap(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game, argc, argv);
	init_window(&game);
	clean_game(&game);
	return (EXIT_SUCCESS);
}
