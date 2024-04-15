/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:10:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/15 09:55:53 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

static void	verify_color(char *color)
{
	char	**split_color;

	split_color = ft_split(color, ',');
	if (!split_color)
		error(NULL, true, "malloc");
	if (ft_arrsize((void **)color) != 3)
		item_error(color, INV_COLOR);
	// gestionar espacios ?? strtrim
	// nums entre 0 y 255 incluidos
	// cualquier otro caracter lanzar error
}

void	manage_colors(t_game *game, char **line)
{
	(void)game;
	if (ft_arrsize((void **)line) < 2)
		item_error(line[0], MISSING_COLOR);
	else if (ft_arrsize((void **)line) > 2)
		item_error(line[0], TOO_MUCH_COLOR);
	verify_color(line[1]);
}
