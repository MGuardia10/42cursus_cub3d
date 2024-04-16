/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:10:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/16 10:07:21 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

static int	ft_atoi_mod(char *str, char *color)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	if (!ft_isdigit(str[i]))
	{
		if (str[i] == '+')
			i++;
		else if (str[i] == '-')
			(free(str), item_error(color, NEGATIVE_COLOR));
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		(free(str), item_error(color, INV_CHAR_COLOR));
	if (result < 0 || result > 255)
		(free(str), item_error(color, MAX_NUM_COLOR));
	return (result);
}

static int	*verify_color(char *color)
{
	char	**split_color;
	int		i;
	char	*color_trim;
	int		*color_arr;

	split_color = ft_split(color, ',');
	if (!split_color)
		error(NULL, true, "malloc");
	if (ft_arrsize((void **)split_color) != 3)
		item_error(color, INV_COLOR);
	color_arr = ft_calloc(3, sizeof(int));
	if (!color_arr)
		error(NULL, true, "malloc");
	i = -1;
	while (++i < 3)
	{
		color_trim = ft_strtrim(split_color[i], " ");
		if (!color_trim)
			error(NULL, true, "malloc");
		color_arr[i] = ft_atoi_mod(color_trim, color);
		free(color_trim);
	}
	ft_free_matrix((void **)split_color);
	return (color_arr);
}

void	manage_floor(t_map *map, int *color_arr)
{
	static int flag;

	if (flag == 1)
	{
		free(color_arr);
		item_error("F", FLOOR_TWICE);
	}
	map->floor.r = color_arr[0];
	map->floor.g = color_arr[1];
	map->floor.b = color_arr[2];
	flag = 1;
}

void	manage_ceiling(t_map *map, int *color_arr)
{
	static int flag;

	if (flag == 1)
	{
		free(color_arr);
		item_error("C", CEILING_TWICE);
	}
	map->ceiling.r = color_arr[0];
	map->ceiling.g = color_arr[1];
	map->ceiling.b = color_arr[2];
	flag = 1;
}

void	manage_colors(t_game *game, char **line)
{
	int	*color_arr;
	
	if (ft_arrsize((void **)line) < 2)
		item_error(line[0], MISSING_COLOR);
	else if (ft_arrsize((void **)line) > 2)
		item_error(line[0], TOO_MUCH_COLOR);
	color_arr = verify_color(line[1]);
	if (!ft_strcmp(line[0], "F"))
		manage_floor(&game->map, color_arr);
	else if (!ft_strcmp(line[0], "C"))
		manage_ceiling(&game->map, color_arr);
	free(color_arr);
}
