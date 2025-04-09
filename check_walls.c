/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:36:01 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:45:54 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_size(char **map, size_t *width, size_t *height)
{
	*height = 0;
	while (map[*height])
		(*height)++;
	*width = ft_strlen(map[0]);
	if (map[0][*width - 1] == '\n')
		(*width)--;
}

int	check_horizontal_walls(char **map, size_t width, size_t height)
{
	size_t	j;

	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	sanitize_and_check_vertical_walls(char **map, size_t height)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
		{
			map[i][len - 1] = 0;
			len--;
		}
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(char **map)
{
	size_t width, height;

	get_map_size(map, &width, &height);
	if (!check_horizontal_walls(map, width, height))
		return (0);
	if (!sanitize_and_check_vertical_walls(map, height))
		return (0);
	return (1);
}