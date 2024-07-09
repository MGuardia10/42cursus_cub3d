/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:16:09 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 15:29:14 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function `empty_found` searches for an empty element in a 2D array and
 * returns its coordinates if found.
 * 
 * @param map A 2D array representing a map.
 * @param x a pointer to an integer that represents the x-coordinate.
 * @param y a pointer to an integer that represents the y-coordinate.
 * 
 * @return a boolean value - `true` if an empty space is found in the map, and
 * `false` if no empty space is found.
 */
bool	empty_found(char **map, int *x, int *y)
{
	int	i;
	int	j;

	if (!map)
		return (false);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == EMPTY)
			{
				if (y)
					*y = i;
				if (x)
					*x = j;
				return (true);
			}
		}
	}
	return (false);
}

/**
 * The function checks if a given position on a map is invalid based on certain
 * conditions.
 * 
 * @param map A 2D array representing a map where each element is a character.
 * @param x X represents the horizontal position on the map.
 * @param y Y represents the vertical position or row index on the 2D map array.
 * 
 * @return a boolean value - `true` if the position at coordinates (x, y) on the
 * map is considered invalid, and `false` if the position is valid.
 */
static bool	is_invalid_position(char **map, int x, int y)
{
	if (x < 0 \
		|| y < 0 \
		|| (size_t)y >= ft_arrsize((void **)map) \
		|| (size_t)x >= ft_strlen(map[y]))
		return (true);
	if (ft_strlen(map[y]) <= (size_t)x)
		return (true);
	if (map[y][x] == ' ')
		return (true);
	return (false);
}

/**
 * The flood_fill function recursively fills connected areas in a 2D map with
 * '1' starting from a given position (x, y).
 * 
 * @param map A 2D array representing the map.
 * @param x The parameter `x` represents the x-coordinate of the current
 * position on the map.
 * @param y The parameter `y` represents the vertical position on the map.
 * 
 * @return a value indicating whether the flood fill operation was successful or
 * not.
 */
int	flood_fill(char **map, int x, int y)
{
	int	status;

	if (is_invalid_position(map, x, y))
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	status = 0;
	status += flood_fill(map, x, y - 1);
	status += flood_fill(map, x + 1, y);
	status += flood_fill(map, x, y + 1);
	status += flood_fill(map, x - 1, y);
	return (status != 0);
}
