/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:31:07 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/10 15:30:36 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/inc/colors.h"

/**
 * The function `item_error` displays an error message with optional item
 * information and exits the program with a failure status.
 * 
 * @param item a string that represents the item or object related to the error.
 * @param error a string that represents the error message to be displayed.
 */
void	item_error(t_game *game, char *item, char *error)
{
	ft_putstr_fd(HRED"Error: ", STDERR_FILENO);
	if (item)
	{
		ft_putstr_fd(item, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(RES, STDERR_FILENO);
	clean_game(game);
	exit(EXIT_FAILURE);
}

/**
 * The function `error` displays an error message with optional additional
 * information and exits the program with a failure status.
 * 
 * @param error a string that represents the error message to be displayed.
 * @param flag The `flag` parameter is a boolean variable that is used to
 * determine whether to display additional error information using `perror`.
 * @param pstr a string that is used as a parameter for `perror` when flag is
 * true.
 */
void	error(t_game *game, char *error, bool flag, char *pstr)
{
	ft_putstr_fd(HRED"Error: ", STDERR_FILENO);
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	if (flag == true)
		perror(pstr);
	ft_putstr_fd(RES, STDERR_FILENO);
	clean_game(game);
	exit(EXIT_FAILURE);
}
