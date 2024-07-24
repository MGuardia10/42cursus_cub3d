/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:58:25 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/24 22:56:11 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * The function checks if a given string consists only of whitespace characters.
 * 
 * @param str The parameter `str` represents a string.
 * 
 * @return a boolean value. If the input string `str` is empty or contains only
 * whitespace characters, the function will return true. Otherwise, it will 
 * return false.
 */
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

/**
 * The function `is_texture` checks if a given string matches specific texture
 * key names.
 * 
 * @param str The string that needs to be compared with texture identifiers 
 * "NO", "SO", "WE", or "EA".
 * 
 * @return A boolean value based on whether the `str` matches any of the texture
 * key names "NO", "SO", "WE", or "EA".
 */
bool	is_texture(char *str)
{
	return (!ft_strcmp(str, "NO")
		|| !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE")
		|| !ft_strcmp(str, "EA"));
}

/**
 * The function checks if the input string is equal to "F" or "C".
 * 
 * @param str The string to be compared.
 * 
 * @return a boolean value, which is determined by whether the input string is
 * equal to "F" or "C".
 */
bool	is_color(char *str)
{
	return (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"));
}

/**
 * The function `get_color` takes a `t_color` struct as input and returns a
 * combined RGB color value.
 * 
 * @param item represents a color with red, green, and blue components.
 * 
 * @return a single integer value that represents the RGB color components of
 * the input `t_color` item.
 */
int	get_color(t_color item)
{
	return ((item.r << 24) | (item.g << 16) | (item.b << 8) | (0xFF));
}
