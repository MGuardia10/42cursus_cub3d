/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:42:46 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/12 11:38:54 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../libft/inc/colors.h"

/*
	- Verificar que se pasa un mapa
	- que sea valido (que sea un archivo terminado en .cub, que no sea un directorio, que tenga permisos)
	- 
*/
int	args_parsing(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, \
				HRED"Error: Invalid number of arguments\n"RES);
		return (1);
	}
	if (!ft_is_format(argv[1], ".cub"))
	{
		ft_dprintf(STDERR_FILENO, \
				HRED"Error: file with .cub extension is required\n"RES);
		return (1);
	}
	if (!ft_is_readable(argv[1]))
	{
		ft_dprintf(STDERR_FILENO, HRED"Error: ");
		perror(argv[1]);
		return (1);
	}
	printf("todo ok hasta aqui");
	return (0);
}
