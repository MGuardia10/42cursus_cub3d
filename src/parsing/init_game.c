/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:45:16 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/16 10:16:43 by mguardia         ###   ########.fr       */
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
static void	verify_args(int argc, char **argv)
{
	if (argc != 2)
		error(WRONG_N_ARGS, false, NULL);
	if (!ft_is_format(argv[1], ".cub"))
		error(WRONG_EXT_CUB, false, NULL);
	if (!ft_is_readable(argv[1]))
		error(NULL, true, argv[1]);
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
	return (file);
}

static void	file_items_parsing(t_game *game, char **arr)
{
	int		i;
	char	**split_line;

	i = 0;
	while (i < 6)
	{
		if (!arr[i])
			error(INV_FILE, false, NULL);
		split_line = ft_split(arr[i], ' ');
		if (!split_line)
			error(NULL, true, "malloc");
		if (is_texture(split_line[0]))
			manage_textures(game, split_line);
		else if (is_color(split_line[0]))
			manage_colors(game, split_line);
		else
			item_error(split_line[0], INV_TYPE_ID);
		ft_free_matrix((void **)split_line);
		i++;
	}
}

// static void	file_map_parsing(t_game *game, char **arr)
// {
// }

int	init_game(t_game *game, int argc, char **argv)
{
	char	*file_str;
	char	**file_arr;

	verify_args(argc, argv);
	file_str = get_file(argv[1]);
	if (!file_str || is_empty(file_str))
		error(EMPTY_FILE, false, NULL);
	file_arr = ft_split(file_str, '\n');
	free(file_str);
	if (!file_arr)
		(error(NULL, true, "malloc"));
	if (!file_arr[0])
		error(EMPTY_FILE, false, NULL);
	ft_memset(game, 0, sizeof(t_game));
	file_items_parsing(game, file_arr);
	// file_map_parsing(game, file_arr);

	printf("F colors --> [%d] [%d] [%d]\n", game->map.floor.r, game->map.floor.g, game->map.floor.b);
	printf("C colors --> [%d] [%d] [%d]\n", game->map.ceiling.r, game->map.ceiling.g, game->map.ceiling.b);
	
	return (0);
}
