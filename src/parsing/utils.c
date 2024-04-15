/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:58:25 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/15 09:51:48 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_texture(char *str)
{
	return (!ft_strcmp(str, "NO")
		|| !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE")
		|| !ft_strcmp(str, "EA"));
}

bool	is_color(char *str)
{
	return (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"));
}
