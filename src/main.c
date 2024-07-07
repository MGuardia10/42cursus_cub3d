/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/07 02:28:28 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_parsing(t_game *game)
{
	int	i;

	printf("\n-------------- MAP ------------------\n");
	printf("\nfile path ---> [%s]\n", game->map.file);
	printf("\n--> TEXTURES\n");
	printf("NO ---> [%s]\n", game->map.textures.north);
	printf("SO ---> [%s]\n", game->map.textures.south);
	printf("EA ---> [%s]\n", game->map.textures.east);
	printf("WE ---> [%s]\n", game->map.textures.west);
	printf("\n--> COLORS\n");
	printf("FLOOR   ---> [%d, %d, %d] - [%d]\n", game->map.floor.r, \
			game->map.floor.g, game->map.floor.b, game->map.floor.rgb);
	printf("CEILING ---> [%d, %d, %d] - [%d]\n", game->map.ceiling.r, \
			game->map.ceiling.g, game->map.ceiling.b, game->map.ceiling.rgb);
	printf("\n--> PLAYER\n");
	printf("pos ---> [%c]\n", game->player.orientation);
	printf("x ---> [%d]\n", game->player.x);
	printf("y ---> [%d]\n", game->player.y);
	printf("\n--> MAP\n");
	i = 0;
	while (game->map.map_cpy[i])
		printf("%s\n", game->map.map_cpy[i++]);
}

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	mlx_image_t *img = mlx_new_image(game->mlx, TILESIZE, TILESIZE);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	while (game->map.map_cpy[i])
	{
		j = 0;
		while (game->map.map_cpy[i][j])
		{
			if (game->map.map_cpy[i][j] == '1')
				mlx_image_to_window(game->mlx, img, j * TILESIZE, i * TILESIZE);
			j++;
		}
		i++;
	}
}

void	init_window(t_game *game)
{
	//int32_t	sheight;
	//int32_t swidth;

	//mlx_get_monitor_size(0, &swidth, &sheight);
	game->mlx = mlx_init(SHEIGHT, SWIDTH, "cub3d", false);
	print_map(game);
	castrays(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game, argc, argv);
	print_parsing(&game);
	init_window(&game);
	mlx_loop(game.mlx);
}
