/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:22:45 by raalonso          #+#    #+#             */
/*   Updated: 2024/07/16 15:51:13 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(t_game *game, int map_x, int map_y, int color)
{
	int			s_x;
	int			s_y;
	uint32_t	i;
	uint32_t	j;

	s_x = map_x * (game->map->map_img->height / game->map->max_y);
	s_y = map_y * (game->map->map_img->height / game->map->max_y);
	i = 0;
	while (i < game->map->map_img->height / game->map->max_y)
	{
		j = 0;
		while (j < game->map->map_img->height / game->map->max_y)
		{
			mlx_put_pixel(game->map->map_img, s_x + j, s_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	p_x;
	int	p_y;
	uint32_t	i;
	uint32_t	j;
	int		color = 0xCAE8FF;

	p_x = floor((game->player.x / TILESIZE) * (game->map->map_img->height / game->map->max_y));
	p_y = floor((game->player.y / TILESIZE) * (game->map->map_img->height / game->map->max_y));
	p_x -= (game->map->map_img->height / game->map->max_y) / 2;
	p_y -= (game->map->map_img->height / game->map->max_y) / 2;
	i = 0;
	while (i < game->map->map_img->height / game->map->max_y)
	{
		j = 0;
		while (j < game->map->map_img->height / game->map->max_y)
		{
			mlx_put_pixel(game->map->map_img, p_x + j, p_y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int map_x;
	int map_y;
	int color;

	map_y = 0;
	while (game->map->map_cpy[map_y])
	{
		map_x = 0;
		while (game->map->map_cpy[map_y][map_x])
		{
			if (game->map->map_cpy[map_y][map_x] == '1')
				color = game->map->ceiling.rgb + 1500;
			else if (game->map->map_cpy[map_y][map_x] == ' ')
				color = 0x00000000;
			else
				color = 0xFFFFFFFF;
			draw_square(game, map_x, map_y, color);
			map_x++;
		}
		map_y++;
	}
	draw_player(game);
}

void	game_loop(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	castrays(game);
	player_controller(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		render_minimap(game);
}

double	get_p_angle(t_game *game)
{
	if (game->player.orientation == NORTH)
		return (3 * M_PI / 2);
	else if (game->player.orientation == SOUTH)
		return (M_PI / 2);
	else if (game->player.orientation == WEST)
		return (M_PI);
	else if (game->player.orientation == EAST)
		return (0);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	game->player.rd_fov = (FOV * M_PI) / 180;
	game->player.angle = get_p_angle(game);
	game->player.ws = 0;
	game->player.ad = 0;
}

void	init_minimap(t_game *game)
{
	int	m_w;
	int	m_h;
	
	m_w = floor(game->map->max_x * (SWIDTH / 100));
	m_h = floor(game->map->max_y * (SHEIGHT / 100));
	game->map->map_img = mlx_new_image(game->mlx, m_w, m_h);
	mlx_image_to_window(game->mlx, game->map->map_img, SWIDTH / 20, SHEIGHT / 20);
}

void mousepress(mouse_key_t button, action_t action, modifier_key_t mods, void* gameptr)
{
	t_game	*game;

	(void)mods;
	game = (t_game *)gameptr;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
	{
		game->mouse_rotation = !game->mouse_rotation;
		if (game->mouse_rotation)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		else {
			game->player.rotate = 0;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		}
	}
}

void cursor_move(double xpos, double ypos, void *gameptr)
{
	static int	delta_x;
	t_game		*game;
	
	game = (t_game *)gameptr;

	(void)ypos;

	//printf("xpos: %d || delta_x; %d\n", (int)xpos, delta_x);

	if (game->mouse_rotation) {
		delta_x = (int)xpos - (SWIDTH / 2);
		if (delta_x > 10) {
			//rotate right
			game->player.rotate = 1;
		}
		else if (delta_x < -10) {
			// rotate left
			game->player.rotate = -1;
		} else
			game->player.rotate = 0;
		mlx_set_mouse_pos(game->mlx, SWIDTH / 2, SHEIGHT / 2);
		delta_x = SWIDTH / 2;
	}
	//delta_x = (int)xpos;

}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(SWIDTH, SHEIGHT, "cub3d", false);
	if (!game->mlx)
		error(game, NULL, true, "malloc");
	game->pixel = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	if (!game->pixel) {
		mlx_close_window(game->mlx);
		error(game, NULL, true, "malloc");
	}
	if (mlx_image_to_window(game->mlx, game->pixel, 0, 0) < 0) {
		mlx_close_window(game->mlx);
		error(game, NULL, true, "malloc");
	}
	init_player(game);
	if (SWIDTH >= 100 && SHEIGHT >= 100)
		init_minimap(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &keypress, game);
	mlx_mouse_hook(game->mlx, &mousepress, game);
	mlx_cursor_hook(game->mlx, &cursor_move, game);
	mlx_close_hook(game->mlx, &terminate_game, game);
	mlx_loop(game->mlx);
}
