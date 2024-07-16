/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:22 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/16 17:36:04 by mguardia         ###   ########.fr       */
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
 * The function `cpy_map` copies a 2D array of strings starting from a specified
 * index `i` and returns the copied array.
 * 
 * @param arr represents a 2D array of strings.
 * @param i The parameter `i` in the `cpy_map` function represents the index at
 * which to start copying elements from the input `arr` array of strings. The
 * function will copy the strings starting from index `i` until the end of the
 * array.
 * 
 * @return The function `cpy_map` is returning a pointer to a pointer to a
 * character (`char **`).
 */
char	**cpy_map(t_game *game, char **arr, int i,  bool flag)
{
	char	**cpy;
	int		j;

	cpy = ft_calloc(ft_arrsize((void **)arr + i) + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	if (flag)
	{
		game->map->x_row = ft_calloc(ft_arrsize((void **)arr + i), sizeof(int));
		if (!game->map->x_row)
			return (ft_free_matrix((void **)cpy), NULL);
	}
	j = 0;
	while (arr[i])
	{
		if (flag)
			game->map->x_row[j] = ft_strlen(arr[i]);
		cpy[j] = ft_strdup(arr[i]);
		if (!cpy[j])
			return (ft_free_matrix((void **)cpy), NULL);
		j++;
		i++;
	}
	return (cpy);
}

/**
 * The function checks the limits of a map represented as a 2D array of chars.
 * 
 * @param map a 2D array of characters representing a map.
 * 
 * @return a boolean value - `true` if the map limits are valid, and `false` if
 * they are invalid.
 */
bool	valid_map_limits(t_game *game, t_map *map)
{
	char	**map_cpy;
	int		x;
	int		y;
	bool	err;

	map_cpy = cpy_map(game, map->map_cpy, 0, false);
	if (!map_cpy)
		error(game, NULL, true, "malloc");
	err = false;
	while (!err && empty_found(map_cpy, &x, &y))
		err = flood_fill(map_cpy, x, y);
	ft_free_matrix((void **)map_cpy);
	return (!err);
}
