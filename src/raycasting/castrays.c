/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:26:04 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/06 19:29:44 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_h_inter(t_game *game)
{
	
}

double	get_v_inter(t_game *game)
{
	
}

void	castrays(t_game *game)
{
	int	ray;
	double h_inter;
	double v_inter;

	game->ray.angle = 1; //start angle
	while (ray < SWIDTH)
	{
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		if (h_inter <= v_inter)
			game->ray.distance = h_inter;
		else
			game->ray.distance = v_inter;
		// render wall
		ray++;
		// next angle
	}
}