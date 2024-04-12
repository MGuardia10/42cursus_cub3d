/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/12 11:46:26 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (args_parsing(argc, argv))
		return (EXIT_FAILURE);
	if (init_cub3d(&cub3d, argv[1]))
		return (EXIT_FAILURE);
	// mlx stuff
	return (EXIT_SUCCESS);
	
}