/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:06:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/07 02:57:16 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

static void	verify_path(char *path)
{
	if (!ft_is_format(path, ".xpm42"))
		item_error(path, WRONG_EXT_XPM);
	if (!ft_is_readable(path))
		error(NULL, true, path);
	// verificar ejecucion ??
}

void	get_texture(char **texture_item, char **line)
{
	if (!texture_item[0])
	{
		texture_item[0] = ft_strdup(line[1]);
		if (!texture_item[0])
			error(NULL, true, "malloc");
	}
	else
		item_error(line[0], TEXTURE_TWICE);
	// hacer movidas de mlx si es que hay que hacer algo
}

void	manage_textures(t_game *game, char **line)
{
	if (ft_arrsize((void **)line) < 2)
		item_error(line[0], MISSING_PATH);
	else if (ft_arrsize((void **)line) > 2)
		item_error(line[0], TOO_MUCH_PATH);
	verify_path(line[1]);
	(void)game;
	if (!ft_strcmp(line[0], "NO"))
		get_texture(&game->map.textures.north, line);
	else if (!ft_strcmp(line[0], "SO"))
		get_texture(&game->map.textures.south, line);
	else if (!ft_strcmp(line[0], "WE"))
		get_texture(&game->map.textures.west, line);
	else if (!ft_strcmp(line[0], "EA"))
		get_texture(&game->map.textures.east, line);
	// algo de mlx creo
}
