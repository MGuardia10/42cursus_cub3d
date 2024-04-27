/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:22 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/26 19:20:42 by mguardia         ###   ########.fr       */
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
