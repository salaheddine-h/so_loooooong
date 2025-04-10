/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:17:05 by salhali           #+#    #+#             */
/*   Updated: 2025/04/10 20:49:33 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_map(const char *Pathname_map, t_game *game)
{
	int		fd;
	int		total_lines;
	int		i;
	char	**map;
	char	*stripped;

	total_lines = count_lines(Pathname_map);
	map = malloc(sizeof(char *) * (total_lines + 1));
	if (!map)
		return (NULL);
	fd = open(Pathname_map, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i] != NULL)
		map[++i] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	game->cpy_map = copy_map(map);
	game->win_y = i;
	stripped = ft_strtrim(map[0], "\n");
	game->win_x = ft_strlen(stripped);
	free(stripped);
	return (map);
}

int	check_shape(char **map)
{
	size_t	i;
	size_t	len;
	size_t	curr_len;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	if (map[0][len - 1] == '\n')
		len--;
	i = 1;
	while (map[i])
	{
		curr_len = ft_strlen(map[i]);
		if (map[i][curr_len - 1] == '\n')
			curr_len--;
		if (curr_len != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_map(char **map)
{
	if (check_shape(map) == 0)
	{
		error("Error: Map is not valid.\n");
		return (0);
	}
	if (check_walls(map) == 0)
	{
		error("Error: Map Walls are not valid.\n");
		return (0);
	}
	if (check_player(map) == 0)
	{
		error("Error: Map does not contain required player.\n");
		return (0);
	}
	return (1);
}

void	check_dotber(char **av)
{
	int		len;
	char	*str;

	str = ".ber";
	len = ft_strlen(av[1]);

	if (len >= 4)
	{
		if (ft_strcmp(av[1] + len - 4, str) != 0)
		{
			error("Error is not the good argument !");
		}
	}
}
