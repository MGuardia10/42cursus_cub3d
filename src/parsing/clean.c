/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:25 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/16 17:37:31 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	free_textures(t_texture *textures)
{
	if (textures->north_tx)
		mlx_delete_texture(textures->north_tx);
	if (textures->south_tx)
		mlx_delete_texture(textures->south_tx);
	if (textures->west_tx)
		mlx_delete_texture(textures->west_tx);
	if (textures->east_tx)
		mlx_delete_texture(textures->east_tx);
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
		if (game->map->file_arr)
			ft_free_matrix((void **) game->map->file_arr);
		if (game->map->item_line)
			ft_free_matrix((void **) game->map->item_line);
		if (game->map->color_arr)
			free(game->map->color_arr);
		if (game->map->map_cpy)
			ft_free_matrix((void **)game->map->map_cpy);
		if (game->map->x_row)
			free(game->map->x_row);
		free_textures(&game->map->textures);
		free(game->map);
	}
}

void	terminate_game(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	if (game->mlx->window)
		mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	clean_game(game);
	exit(EXIT_SUCCESS);
}
