/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:11:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/15 09:50:17 by mguardia         ###   ########.fr       */
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
# define TOO_MUCH_COLOR	"too much items found, use noly one rgb color\n"

#endif