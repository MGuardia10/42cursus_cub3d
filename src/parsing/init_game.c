/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:45:16 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/10 15:35:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

/**
 * The function `get_file` reads a file line by line and concatenates the lines
 * into a single string.
 * 
 * @param path The function `get_file` takes a file path as a parameter and
 * reads the contents of the file specified by the path.
 * 
 * @return The function `get_file` is returning a string, which represents the
 * contents of a file read from the specified path.
 */
static char	*get_file(t_game *game, char *path)
{
	int		fd;
	char	*file;
	char	*aux;
	char	*str;

	file = NULL;
	fd = open(path, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (file)
			aux = ft_strdup(file);
		else
			aux = ft_strdup("");
		if (!aux)
			(free(str), close(fd), error(game, NULL, true, "malloc"));
		free(file);
		file = ft_strjoin(aux, str);
		(free(aux), free(str));
		if (!file)
			(close(fd), error(game, NULL, true, "malloc"));
	}
	return (close(fd), file);
}

/**
 * The function `parse_input` checks the number of arguments, file extension,
 * and readability of a specific file. It also fills the file_arr with the file
 * splited by '\n'.
 * 
 * @param game A pointer to a struct named `t_game`. It contains information
 * about the game like the position of the player and the map.
 * @param argc The `argc` parameter represents the number of arguments passed to
 * the program when it is executed.
 * @param argv The `argv` parameter is a pointer to an array of strings, where
 * each string represents a command-line argument passed to the program.
 */
static void	parse_input(t_game *game, int argc, char **argv)
{
	char	*file_str;

	if (argc != 2)
		error(game, WRONG_N_ARGS, false, NULL);
	if (!ft_is_format(argv[1], ".cub"))
		error(game, WRONG_EXT_CUB, false, NULL);
	if (!ft_is_readable(argv[1]))
		error(game, NULL, true, argv[1]);
	game->map->file = ft_strdup(argv[1]);
	if (!game->map->file)
		error(game, NULL, true, "malloc");
	file_str = get_file(game, argv[1]);
	if (!file_str || is_empty(file_str))
		error(game, EMPTY_FILE, false, NULL);
	game->map->file_arr = ft_split(file_str, '\n');
	free(file_str);
	if (!game->map->file_arr)
		(error(game, NULL, true, "malloc"));
	if (!game->map->file_arr[0])
		error(game, EMPTY_FILE, false, NULL);
}

/**
 * The function parses and manages different types of items in a game based on
 * the input array.
 * 
 * @param game The `game` parameter is a pointer to a `t_game` struct.
 * @param arr `arr` is a pointer to an array of strings, where each string
 * represents a line of text that needs to be parsed for game items.
 * @param i an integer pointer used as a reference to keep track of the current
 * index while parsing an array of strings (`arr`).
 */
static void	file_items_parsing(t_game *game, char **arr, int *i)
{
	while (*i < 6)
	{
		if (!arr[*i])
			error(game, INV_FILE, false, NULL);
		game->map->item_line = ft_split(arr[*i], ' ');
		if (!game->map->item_line)
			error(game, NULL, true, "malloc");
		if (!game->map->item_line[0])
			item_error(game, NULL, EMPTY_ITEM);
		else if (is_texture(game->map->item_line[0]))
			manage_textures(game, game->map->item_line);
		else if (is_color(game->map->item_line[0]))
			manage_colors(game, game->map->item_line);
		else
			item_error(game, game->map->item_line[0], INV_TYPE_ID);
		ft_free_matrix((void **)game->map->item_line);
		(*i)++;
	}
	if (game->map->floor.rgb == game->map->ceiling.rgb)
		item_error(game, NULL, SAME_COLORS);
}

/**
 * The function parses a file map, checks for errors, finds the player position,
 * copies the map in struct, and validates map limits.
 * 
 * @param game The `game` parameter is a pointer to a `t_game` struct.
 * @param arr is an array of strings. Each string in the array likely represents
 * a row of a game map that is being parsed.
 * @param i an integer pointer used as a reference to keep track of the current
 * index while parsing an array of strings (`arr`).
 */
static void	file_map_parsing(t_game *game, char **arr, int *i)
{
	int		j;
	int		n_player;
	size_t	row_len;

	j = *i - 1;
	n_player = 0;
	row_len = 0;
	while (arr[++j])
	{
		if (is_empty(arr[j]))
			item_error(game, NULL, EMPTY_MAP);
		if (has_invalid_chars(arr[j]))
			item_error(game, NULL, INV_CHAR_MAP);
		n_player = find_player(&game->player, arr[j], j - *i);
		row_len = ft_strlen(arr[j]);
		if (row_len > game->map->max_x)
			game->map->max_x = row_len;
	}
	if (n_player != 1)
		item_error(game, NULL, PLAYER_MAP);
	game->map->map_cpy = cpy_map(arr, *i);
	if (!valid_map_limits(game, game->map))
		error(game, INV_MAP_LIMITS, false, NULL);
	game->map->max_y = j - *i;
}

/**
 * The function `init_game` initializes a game structure by parsing input
 * arguments and file contents.
 * 
 * @param game a pointer to a structure of type `t_game`.
 * @param argc The `argc` parameter in the `init_game` function represents the
 * number of arguments passed to the program when it is executed.
 * @param argv an array of strings that represent the command-line arguments
 * passed to the program when it was executed.
 */
void	init_game(t_game *game, int argc, char **argv)
{
	int		i;

	ft_memset(game, 0, sizeof(t_game));
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!game->map)
		error(game, NULL, true, "malloc");
	parse_input(game, argc, argv);
	i = 0;
	file_items_parsing(game, game->map->file_arr, &i);
	file_map_parsing(game, game->map->file_arr, &i);
}
