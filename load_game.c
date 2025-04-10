/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:24:52 by salhali           #+#    #+#             */
/*   Updated: 2025/04/10 15:30:32 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"./textures/floor.xpm", &width, &height);
	if (!game->textures.floor)
		return (0);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"./textures/player.xpm", &width, &height);
	if (!game->textures.player)
		return (0);
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"./textures/wall.xpm", &width, &height);
	if (!game->textures.wall)
		return (0);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"./textures/collectible.xpm", &width, &height);
	if (!game->textures.collectible)
		return (0);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"./textures/exit.xpm", &width, &height);
	if (!game->textures.exit)
		return (0);
	return (1);
}

void	move_player(t_game *game, int dx, int dy)
{
	static int	move_count = 0;
	int			current_x;
	int			current_y;
	int			new_x;
	int			new_y;

	if (!find_player_pos(game, &current_x, &current_y))
		return ;
	new_x = current_x + dx;
	new_y = current_y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'E' && !check_all_collected(game))
		return ;
	if (game->map[new_y][new_x] == 'E' && check_all_collected(game))
	{
		ft_printf("Moves : %d\n", ++move_count);
		ft_printf("You won!\n");
		close_window(game);
	}
	game->map[current_y][current_x] = '0';
	game->map[new_y][new_x] = 'P';
	ft_printf("Moves: %d\n", ++move_count);
	render_map(game);
}

int	find_player_pos(t_game *game, int *x_pos, int *y_pos)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				*x_pos = x;
				*y_pos = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_all_collected(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
