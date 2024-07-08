/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/08 20:06:00 by raalonso         ###   ########.fr       */
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
	printf("x ---> [%f]\n", game->player.x);
	printf("y ---> [%f]\n", game->player.y);
	printf("\n--> MAP\n");
	i = 0;
	while (game->map.map_cpy[i])
		printf("%s\n", game->map.map_cpy[i++]);
}

void	print_map(t_game *game)
{
	int tile = TILESIZE / 3;
	int	i;
	int	j;

	i = 0;
	mlx_image_t *img = mlx_new_image(game->mlx, tile, tile);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_t *img2 = mlx_new_image(game->mlx, tile, tile);
	ft_memset(img2->pixels, 200, img->width * img->height * sizeof(int32_t));
	while (game->map.map_cpy[i])
	{
		j = 0;
		while (game->map.map_cpy[i][j])
		{
			if (game->map.map_cpy[i][j] == '1')
				mlx_image_to_window(game->mlx, img, j * tile, i * tile);
			else if (game->map.map_cpy[i][j] == 'S')
				mlx_image_to_window(game->mlx, img2, j * tile, i * tile);
			j++;
		}
		i++;
	}
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(SWIDTH, SHEIGHT, "cub3d", false);
	game->pixel = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	mlx_image_to_window(game->mlx, game->pixel, 0, 0);
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	game->player.rd_fov = (FOV * M_PI) / 180;
	game->player.angle = M_PI;
	game->player.ws = 0;
	game->player.ad = 0;
	print_map(game);
}

void	game_loop(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	castrays(game);
	player_controller(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game, argc, argv);
	print_parsing(&game);
	init_window(&game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &keypress, &game);
	mlx_loop(game.mlx);
}
