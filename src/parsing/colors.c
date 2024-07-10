/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:10:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/10 15:22:48 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

/**
 * The function `ft_atoi_mod` converts a string to an integer while handling
 * special cases and error conditions related to color values.
 * 
 * @param str a string that contains numerical characters.
 * @param color a string that it is used in error handling to provide more
 * context or information about the error that occurred.
 * 
 * @return The function `ft_atoi_mod` is returning an integer value, which is
 * the result of converting the input string `str` to an integer.
 */
static int	ft_atoi_mod(t_game *game, char **colors, int i, char *color)
{
	long long	result;
	int			j;

	result = 0;
	j = 0;
	if (!ft_isdigit(colors[i][j]))
	{
		if (colors[i][j] == '+')
			j++;
		else if (colors[i][j] == '-')
			(ft_free_matrix((void **)colors), item_error(game, color, NEGATIVE_COLOR));
	}
	while (ft_isdigit(colors[i][j]))
	{
		result = result * 10 + (colors[i][j] - '0');
		j++;
	}
	if (colors[i][j])
		(ft_free_matrix((void **)colors), item_error(game, color, INV_CHAR_COLOR));
	if (result < 0 || result > 255)
		(ft_free_matrix((void **)colors), item_error(game, color, MAX_NUM_COLOR));
	return (result);
}

/**
 * The function `verify_color` takes a string representing a color, splits it
 * into RGB components, trims and converts each component to an integer, and
 * returns an array of the RGB values.
 * 
 * @param color The `verify_color` function takes a string `color` as input.
 * This string represents a color in RGB format, with the values separated by
 * commas.
 * 
 * @return An integer pointer to an array of three integers representing the RGB
 * values of the input color.
 */
static void	verify_color(t_game *game, char *color)
{
	char	**colors;
	int		i;

	colors = ft_split(color, ',');
	if (!colors)
		error(game, NULL, true, "malloc");
	if (ft_arrsize((void **)colors) != 3)
		(ft_free_matrix((void **) colors), item_error(game, color, INV_COLOR));
	game->map->color_arr = ft_calloc(3, sizeof(int));
	if (!game->map->color_arr)
		(ft_free_matrix((void **) colors), error(game, NULL, true, "malloc"));
	i = -1;
	while (++i < 3)
		game->map->color_arr[i] = ft_atoi_mod(game, colors, i, color);
	ft_free_matrix((void **)colors);
}

/**
 * The function `manage_floor` sets the floor color in a map structure and
 * handles errors related to duplicate floor keys.
 * 
 * @param map The `map` parameter is a pointer to a structure of type `t_map`.
 * @param color_arr The `color_arr` parameter is an integer array that contains
 * the RGB values for the floor color.
 */
static void	manage_floor(t_game *game, t_map *map, int *color_arr)
{
	static int	flag;

	if (flag == 1)
	{
		free(color_arr);
		item_error(game, "F", FLOOR_TWICE);
	}
	map->floor.r = color_arr[0];
	map->floor.g = color_arr[1];
	map->floor.b = color_arr[2];
	map->floor.rgb = get_color(map->floor);
	flag = 1;
}

/**
 * The function `manage_ceiling` sets the ceiling color in a map structure and
 * handles errors related to duplicate ceiling keys.
 * 
 * @param map The `map` parameter is a pointer to a structure of type `t_map`.
 * @param color_arr The `color_arr` parameter is an integer array that contains
 * the RGB values for the ceiling color.
 */
static void	manage_ceiling(t_game *game, t_map *map, int *color_arr)
{
	static int	flag;

	if (flag == 1)
	{
		free(color_arr);
		item_error(game, "C", CEILING_TWICE);
	}
	map->ceiling.r = color_arr[0];
	map->ceiling.g = color_arr[1];
	map->ceiling.b = color_arr[2];
	map->ceiling.rgb = get_color(map->ceiling);
	flag = 1;
}

/**
 * `manage_colors` takes in a game structure and a line of input, verifies the
 * color information, and then manages either the floor or ceiling color based
 * on the input.
 * 
 * @param game The `game` parameter is a pointer to a `t_game` struct, which
 * contains information about the game state.
 * @param line an array of strings. It is used to store the input line that
 * contains information about managing colors in a game.
 */
void	manage_colors(t_game *game, char **line)
{
	if (ft_arrsize((void **)line) < 2)
		item_error(game, line[0], MISSING_COLOR);
	else if (ft_arrsize((void **)line) > 2)
		item_error(game, line[0], TOO_MUCH_COLOR);
	verify_color(game, line[1]);
	if (!ft_strcmp(line[0], "F"))
		manage_floor(game, game->map, game->map->color_arr);
	else if (!ft_strcmp(line[0], "C"))
		manage_ceiling(game, game->map, game->map->color_arr);
	free(game->map->color_arr);
	game->map->color_arr = NULL;
}
