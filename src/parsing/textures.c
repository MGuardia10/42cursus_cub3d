/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:06:08 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/15 09:56:10 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

static void	verify_path(char *path)
{
	if (!ft_is_format(path, ".xpm"))
		item_error(path, WRONG_EXT_XPM);
	if (!ft_is_readable(path))
		error(NULL, true, path);
}

void	manage_textures(t_game *game, char **line)
{
	if (ft_arrsize((void **)line) < 2)
		item_error(line[0], MISSING_PATH);
	else if (ft_arrsize((void **)line) > 2)
		item_error(line[0], TOO_MUCH_PATH);
	verify_path(line[1]);
	(void)game;
	// ingresar path en struct
	// algo de mlx creo
	// revisar que no haya texturas repetidas
}
