/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:22 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/08 20:27:43 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

/* CASOS A TENER EN CUENTA
	- gestionar caracteres validos
	- gestionar lineas anteriores al mapa
	- gestionar lineas de solo espacios
	- gestionar que los bordes sean paredes
	- Verificar que sea un mapa donde el player se pueda mover

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

bool check_adjacent_items_space(char **map, int i, int j)
{
	// top
	if (map[i - 1] && map[i - 1][j] && map[i - 1][j] != ' ' && map[i - 1][j] != WALL)
		return (false);
	// bottom
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] != ' ' && map[i + 1][j] != WALL)
		return (false);
	// left
	if (map[i][j - 1] && map[i][j - 1] != ' ' && map[i][j - 1] != WALL)
		return (false);
	// right
	if (map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != WALL)
		return (false);
	return (true);
}

bool check_adjacent_items_empty(char **map, int i, int j)
{
	// top
	if (map[i - 1] && map[i - 1][j] && map[i - 1][j] == ' ')
		return (false);
	// bottom
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] == ' ')
		return (false);
	// left
	if (map[i][j - 1] && map[i][j - 1] == ' ')
		return (false);
	// right
	if (map[i][j + 1] && map[i][j + 1] == ' ')
		return (false);
	return (true);
}

bool	first_last_row_limits(char **map, int i, int j)
{
	bool	first_char;

	first_char = true;
	while (map[i][j])
	{
		if (first_char || !map[i][j + 1])
		{
			if(map[i][j] != WALL)
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


bool	middle_row_limits(char **map, int i, int j)
{
	bool	first_char;
	size_t	t_len;
	size_t	b_len;

	first_char = true;
	t_len = ft_strlen(map[i - 1]);
	b_len = ft_strlen(map[i + 1]);

	// printf("\n\ntop row: %s || lines: %zu\n", map[i - 1], t_len);
	// printf("curr row: %s || lines: %zu\n", map[i], ft_strlen(map[i]));
	// printf("bottom row: %s || lines: %zu\n", map[i + 1], b_len);
	while (map[i][j])
	{
		if (first_char || !map[i][j + 1])
		{
			if(map[i][j] != WALL)
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
		j++;
	}
	return (true);
}

bool	valid_map_limits(char **map)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(ft_isspace(map[i][j]))
			j++;
		if (i == 0 || !map[i + 1])
			flag = first_last_row_limits(map, i, j);
		else
			flag = middle_row_limits(map, i, j);
		if (flag == false)
			return (false);
		i++;
	}
	return (true);
}
