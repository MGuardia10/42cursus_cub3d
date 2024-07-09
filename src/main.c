/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 16:01:05 by mguardia         ###   ########.fr       */
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
	printf("x ---> [%d]\n", game->player.x);
	printf("y ---> [%d]\n", game->player.y);
	printf("\n--> MAP\n");
	i = 0;
	while (game->map->map_cpy[i])
		printf("%s\n", game->map->map_cpy[i++]);
}

void	free_textures(t_texture *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
}

void	clean_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
	{
		if (game->map->file)
			free(game->map->file);
		if (game->map->map_cpy)
			ft_free_matrix((void **)game->map->map_cpy);
		free_textures(&game->map->textures);
		free(game->map);
	}
	free(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game, argc, argv);
	print_parsing(&game);
	clean_game(&game);
	return (EXIT_SUCCESS);
}
