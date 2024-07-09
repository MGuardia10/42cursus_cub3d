/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:45:16 by mguardia          #+#    #+#             */
/*   Updated: 2024/07/09 14:17:20 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/errors.h"

/**
 * The function `verify_args` checks the number of arguments, file extension,
 * and readability of a specific file.
 * 
 * @param argc The `argc` parameter represents the number of arguments passed to
 * the program when it is executed.
 * @param argv The `argv` parameter is a pointer to an array of strings, where
 * each string represents a command-line argument passed to the program.
 */
static void	verify_args(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		error(WRONG_N_ARGS, false, NULL);
	if (!ft_is_format(argv[1], ".cub"))
		error(WRONG_EXT_CUB, false, NULL);
	if (!ft_is_readable(argv[1]))
		error(NULL, true, argv[1]);
	game->map->file = ft_strdup(argv[1]);
	if (!game->map->file)
		error(NULL, true, "malloc");
}

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
static char	*get_file(char *path)
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
			(free(str), error(NULL, true, "malloc"));
		file = ft_strjoin(aux, str);
		if (!file)
			(free(str), free(aux), error(NULL, true, "malloc"));
		(free(aux), free(str));
	}
	close(fd);
	return (file);
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
	char	**split_line;

	while (*i < 6)
	{
		if (!arr[*i])
			error(INV_FILE, false, NULL);
		split_line = ft_split(arr[*i], ' ');
		if (!split_line)
			error(NULL, true, "malloc");
		if (!split_line[0])
			item_error(NULL, EMPTY_ITEM);
		else if (is_texture(split_line[0]))
			manage_textures(game, split_line);
		else if (is_color(split_line[0]))
			manage_colors(game, split_line);
		else
			item_error(split_line[0], INV_TYPE_ID);
		ft_free_matrix((void **)split_line);
		(*i)++;
	}
	if (game->map->floor.rgb == game->map->ceiling.rgb)
		item_error(NULL, SAME_COLORS);
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
	int	j;
	int	n_player;

	j = *i - 1;
	n_player = 0;
	while (arr[++j])
	{
		if (is_empty(arr[j]))
			(ft_free_matrix((void **)arr), item_error(NULL, EMPTY_MAP));
		if (has_invalid_chars(arr[j]))
			(ft_free_matrix((void **)arr), item_error(NULL, INV_CHAR_MAP));
		n_player = find_player(&game->player, arr[j], j - *i);
	}
	if (n_player != 1)
		(ft_free_matrix((void **)arr), item_error(NULL, PLAYER_MAP));
	game->map->map_cpy = cpy_map(arr, *i);
	if (!valid_map_limits(game->map))
		(ft_free_matrix((void **)arr), error(INV_MAP_LIMITS, false, NULL));
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
	char	*file_str;
	char	**file_arr;
	int		i;

	ft_memset(game, 0, sizeof(t_game));
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!game->map)
		error(NULL, true, "malloc");
	verify_args(game, argc, argv);
	file_str = get_file(argv[1]);
	if (!file_str || is_empty(file_str))
		error(EMPTY_FILE, false, NULL);
	file_arr = ft_split(file_str, '\n');
	free(file_str);
	if (!file_arr)
		(error(NULL, true, "malloc"));
	if (!file_arr[0])
		error(EMPTY_FILE, false, NULL);
	i = 0;
	file_items_parsing(game, file_arr, &i);
	file_map_parsing(game, file_arr, &i);
	ft_free_matrix((void **)file_arr);
}
