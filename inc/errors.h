/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:11:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/11 19:27:49 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_N_ARGS	"Invalid number of arguments\n"
# define WRONG_EXT_CUB	"file with .cub extension is required\n"
# define WRONG_EXT_XPM	"file with .xpm42 extension is required\n"
# define EMPTY_FILE		"file is empty\n"
# define INV_FILE		"file is not valid\n"
# define INV_TYPE_ID	"not a valid type identifier\n"
# define INV_COLOR		"not a valid rgb color. Example: 220,100,50\n"
# define MISSING_PATH	"path to texture is missing\n"
# define MISSING_COLOR	"color in rgb format is missing\n"
# define TOO_MUCH_PATH	"too much items found, use only one path to texture\n"
# define TOO_MUCH_COLOR	\
				"too much items found, use format [r,g,b] without spaces\n"
# define NEGATIVE_COLOR	"negative found, insert only values from 0 to 255\n"
# define INV_CHAR_CLR	"invalid character, insert only values from 0 to 255\n"
# define MAX_NUM_CLR	"invalid number, insert only values from 0 to 255\n"
# define FLOOR_TWICE	"floor item appears more than once\n"
# define CEILING_TWICE	"ceiling item appears more than once\n"
# define TEXTURE_TWICE	"texture item appears more than once\n"
# define SAME_COLORS	"floor and ceiling colors cannot be the same\n"
# define EMPTY_MAP		"There is an empty line with spaces on map\n"
# define EMPTY_ITEM		"There is an empty line with spaces before map\n"
# define INV_CHAR_MAP	"Map has invalid chars. Only \"01NSWE \" are valid\n"
# define PLAYER_MAP		"Cannot parse player position.\n"
# define INV_MAP_LIMITS	"Map is not well closed/surrounded by walls\n"

#endif