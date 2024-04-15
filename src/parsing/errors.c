/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:31:07 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/15 09:26:53 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/inc/colors.h"

void	item_error(char *item, char *error)
{
	ft_putstr_fd(HRED"Error: ", STDERR_FILENO);
	ft_putstr_fd(item, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error(char *error, bool flag, char *pstr)
{
	ft_putstr_fd(HRED"Error: ", STDERR_FILENO);
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	if (flag == true)
		perror(pstr);
	exit(EXIT_FAILURE);
}
