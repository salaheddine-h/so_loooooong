/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:48 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:21:57 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'X')
	{
		if (map[y][x] == 'E')
			map[y][x] = '1';
		return ;
	}
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	check_unreachable_elements(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	find_player_position(t_game *game, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (game->cpy_map[y])
	{
		x = 0;
		while (game->cpy_map[y][x])
		{
			if (game->cpy_map[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_path(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = -1;
	player_y = -1;
	if (!find_player_position(game, &player_x, &player_y))
		return (0);
	flood_fill(game->cpy_map, player_x, player_y);
	return (check_unreachable_elements(game->cpy_map));
}
