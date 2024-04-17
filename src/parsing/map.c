/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:22 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/17 11:28:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
