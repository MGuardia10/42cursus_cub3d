/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/11 19:23:14 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_parsing(t_game *game)
{
	int	i;

	printf("\n-------------- MAP ------------------\n");
	printf("\nfile path ---> [%s]\n", game->map->file);
	printf("\n--> TEXTURES\n");
	printf("NO ---> [%s]\n", game->map->textures.north);
	printf("SO ---> [%s]\n", game->map->textures.south);
	printf("EA ---> [%s]\n", game->map->textures.east);
	printf("WE ---> [%s]\n", game->map->textures.west);
	printf("\n--> COLORS\n");
	printf("FLOOR   ---> [%d, %d, %d] - [%d]\n", game->map->floor.r, \
			game->map->floor.g, game->map->floor.b, game->map->floor.rgb);
	printf("CEILING ---> [%d, %d, %d] - [%d]\n", game->map->ceiling.r, \
			game->map->ceiling.g, game->map->ceiling.b, game->map->ceiling.rgb);
	printf("\n--> PLAYER\n");
	printf("pos ---> [%c]\n", game->player.orientation);
	printf("x ---> [%f]\n", game->player.x);
	printf("y ---> [%f]\n", game->player.y);
	printf("\n--> MAP\n");
	i = 0;
	printf("max_y --> %d\n", game->map->max_y);
	printf("max_x --> %d\n", game->map->max_x);
	while (game->map->map_cpy[i])
		printf("%s\n", game->map->map_cpy[i++]);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game, argc, argv);
	print_parsing(&game);
	init_window(&game);
	clean_game(&game);
	return (EXIT_SUCCESS);
}
