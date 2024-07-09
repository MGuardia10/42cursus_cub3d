/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:22 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 10:18:30 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function checks if a given string contains any invalid characters.
 * 
 * @param str string neccesary to find any characters other than the defined
 * constants (`EMPTY`, `WALL`, `NORTH`, `SOUTH`, `WEST`, `EAST`) and space
 * character.
 * 
 * @return a boolean value - `true` if the input string contains any character
 * other than EMPTY, WALL, NORTH, SOUTH, WEST, EAST, or space, and `false`
 * otherwise.
 */
bool	has_invalid_chars(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != EMPTY \
			&& str[i] != WALL \
			&& str[i] != NORTH \
			&& str[i] != SOUTH \
			&& str[i] != WEST \
			&& str[i] != EAST \
			&& str[i] != ' ')
			return (true);
	}
	return (false);
}

/**
 * The function `find_player` searches for a player's orientation in a given
 * string and assigns his position.
 * 
 * @param player The `player` parameter is a pointer to a structure of type
 * `t_player`.
 * @param str The `str` parameter is a pointer to a character array that 
 * represents a map where the player's position and orientation are being
 * searched for.
 * @param j The variable `j` in the `find_player` function represents the row
 * index where the player character is located in a 2D grid.
 * 
 * @return The function `find_player` is returning the total number of players
 * found so far, which is stored in the static variable `n_player`.
 */
int	find_player(t_player *player, char *str, int j)
{
	int			i;
	static int	n_player;

	i = -1;
	while (str[++i])
	{
		if (str[i] == NORTH || str[i] == SOUTH \
				|| str[i] == WEST || str[i] == EAST)
		{
			player->orientation = str[i];
			player->x = i;
			player->y = j;
			n_player++;
			break ;
		}
	}
	return (n_player);
}

/**
 * The function `cpy_map` copies a portion of a 2D array of strings into a new
 * dynamically allocated array within a given struct.
 * 
 * @param map a pointer to a structure of type `t_map`.
 * @param arr a pointer to a pointer to char, essentially a 2D array of
 * characters.
 * @param i an integer representing the index at which to start copying elements
 *  from the `arr` array.
 */
void	cpy_map(t_map *map, char **arr, int i)
{
	int	j;

	map->map_cpy = ft_calloc(ft_arrsize((void **)arr + i) + 1, sizeof(char *));
	if (!map->map_cpy)
		error(NULL, true, "malloc");
	j = 0;
	while (arr[i])
	{
		map->map_cpy[j] = ft_strdup(arr[i]);
		if (!map->map_cpy[j])
		{
			ft_free_matrix((void **)map->map_cpy);
			error(NULL, true, "malloc");
		}
		j++;
		i++;
	}
}

/**
 * The function checks the limits of a map represented as a 2D array of chars.
 * 
 * @param map a 2D array of characters representing a map.
 * 
 * @return a boolean value - `true` if the map limits are valid, and `false` if
 * they are invalid.
 */
bool	valid_map_limits(char **map)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		if (i == 0 || !map[i + 1])
			flag = first_last_row_limits(map, i, j);
		else
			flag = middle_row_limits(map, i, j - 1);
		if (flag == false)
			return (false);
		i++;
	}
	return (true);
}
