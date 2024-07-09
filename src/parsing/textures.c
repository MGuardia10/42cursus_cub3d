/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:06:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 14:00:57 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

/**
 * The function checks if a given path has the correct format and is readable.
 * 
 * @param path The `path` parameter is a pointer to a character array, which is
 * used to store the file path that needs to be verified.
 */
static void	verify_path(char *path)
{
	if (!ft_is_format(path, ".xpm"))
		item_error(path, WRONG_EXT_XPM);
	if (!ft_is_readable(path))
		error(NULL, true, path);
}

/**
 * The function assigns to the struct the given texture.
 * 
 * @param texture_item a pointer to a pointer to a character array.
 * @param line an array of strings.
 */
static void	get_texture(char **texture_item, char **line)
{
	if (!texture_item[0])
	{
		texture_item[0] = ft_strdup(line[1]);
		if (!texture_item[0])
			error(NULL, true, "malloc");
	}
	else
		item_error(line[0], TEXTURE_TWICE);
}

/**
 * The function processes texture paths for different elements in the game.
 * 
 * @param game The `game` parameter is a pointer to a structure of type `t_game`.
 *
 * @param line a pointer to a pointer to a character array.
 */
void	manage_textures(t_game *game, char **line)
{
	if (ft_arrsize((void **)line) < 2)
		item_error(line[0], MISSING_PATH);
	else if (ft_arrsize((void **)line) > 2)
		item_error(line[0], TOO_MUCH_PATH);
	verify_path(line[1]);
	(void)game;
	if (!ft_strcmp(line[0], "NO"))
		get_texture(&game->map->textures.north, line);
	else if (!ft_strcmp(line[0], "SO"))
		get_texture(&game->map->textures.south, line);
	else if (!ft_strcmp(line[0], "WE"))
		get_texture(&game->map->textures.west, line);
	else if (!ft_strcmp(line[0], "EA"))
		get_texture(&game->map->textures.east, line);
}
