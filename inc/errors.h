/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:11:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/26 17:11:57 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_N_ARGS	"Invalid number of arguments\n"
# define WRONG_EXT_CUB	"file with .cub extension is required\n"
# define WRONG_EXT_XPM	"file with .xpm extension is required\n"
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
# define INV_CHAR_COLOR	"invalid character, insert only values from 0 to 255\n"
# define MAX_NUM_COLOR	"invalid number, insert only values from 0 to 255\n"
# define FLOOR_TWICE	"floor item appears more than once\n"
# define CEILING_TWICE	"ceiling item appears more than once\n"
# define TEXTURE_TWICE	"texture item appears more than once\n"
# define SAME_COLORS	"floor and ceiling colors cannot be the same\n"
# define EMPTY_MAP		"There is an empty line with spaces on map\n"
# define EMPTY_ITEM		"There is an empty line with spaces before map\n"
# define INV_CHAR_MAP	"Map has invalid chars. Only \"01NSWE \" are valid\n"
# define PLAYER_MAP		"More than one player found.\n"

#endif