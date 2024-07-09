/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:16:09 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 10:33:28 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function checks if the adjacent items around a given position (space) in
 * a map are either empty spaces or walls.
 * 
 * @param map an array of string representing a map.
 * @param i an integer that represents the row index.
 * @param j an integer that represents the column index. 
 * @return a boolean value. It returns `true` if all adjacent items around the
 * position `(i, j)` in the `map` are either empty spaces or walls. Otherwise
 * it return `false`.
 */
static bool	check_adjacent_items_space(char **map, int i, int j)
{
	if (map[i - 1] && map[i - 1][j] && map[i - 1][j] != ' ' \
										&& map[i - 1][j] != WALL)
		return (false);
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] != ' ' \
										&& map[i + 1][j] != WALL)
		return (false);
	if (map[i][j - 1] && map[i][j - 1] != ' ' && map[i][j - 1] != WALL)
		return (false);
	if (map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != WALL)
		return (false);
	return (true);
}

/**
 * The function checks if the adjacent items around a given position (empty) in
 * a map are spaces ' '. It only checks up and down the point given.
 * 
 * @param map an array of string representing a map.
 * @param i an integer that represents the row index.
 * @param j an integer that represents the column index. 
 * @return a boolean value.
 */
static bool	check_adjacent_items_empty(char **map, int i, int j)
{
	if (map[i - 1] && map[i - 1][j] && map[i - 1][j] == ' ')
		return (false);
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] == ' ')
		return (false);
	// if (map[i][j - 1] && map[i][j - 1] == ' ')
	// 	return (false);
	// if (map[i][j + 1] && map[i][j + 1] == ' ')
	// 	return (false);
	return (true);
}

/**
 * The function checks if the characters in the first or last row of a map meet
 * certain conditions.
 * 
 * @param map A 2D array representing a map where each element is a character.
 * @param i an integer that represents the row index.
 * @param j an integer that represents the column index.
 * 
 * @return a boolean value. It returns `true` if the conditions specified in
 * the function are met, and `false` otherwise.
 */
bool	first_last_row_limits(char **map, int i, int j)
{
	bool	first_char;

	first_char = true;
	while (map[i][j])
	{
		if (first_char || !map[i][j + 1])
		{
			if (map[i][j] != WALL)
				return (false);
			first_char = false;
		}
		if (map[i][j] != ' ' && map[i][j] != WALL)
			return (false);
		if (map[i][j] == ' ' && !check_adjacent_items_space(map, i, j))
			return (false);
		j++;
	}
	return (true);
}

/**
 * The function `middle_row_limits` checks the limits and conditions of the
 * middle rows in a map based on certain criteria.
 * 
 * @param map A 2D array representing a map where each element is a character.
 * @param i an integer that represents the row index.
 * @param j an integer that represents the column index.
 * 
 * @return a boolean value.
 */
bool	middle_row_limits(char **map, int i, int j)
{
	bool	first_char;
	size_t	t_len;
	size_t	b_len;

	first_char = true;
	t_len = ft_strlen(map[i - 1]);
	b_len = ft_strlen(map[i + 1]);
	while (map[i][++j])
	{
		if (first_char || !map[i][j + 1])
		{
			if (map[i][j] != WALL)
				return (false);
			first_char = false;
		}
		if (map[i][j] == ' ' && !check_adjacent_items_space(map, i, j))
			return (false);
		else if (map[i][j] == EMPTY && !check_adjacent_items_empty(map, i, j))
			return (false);
		if (ft_strlen(map[i]) > t_len && j >= (int)t_len && map[i][j] != WALL)
			return (false);
		if (ft_strlen(map[i]) > b_len && j >= (int)b_len && map[i][j] != WALL)
			return (false);
	}
	return (true);
}
