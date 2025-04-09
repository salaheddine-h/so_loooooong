/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:24:52 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:47:21 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_game *game)
{
	int width, height;
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

void	render_map(t_game *game)
{
	int	tile_size;

	int x, y;
	y = 0;
	tile_size = 64;
	mlx_clear_window(game->mlx, game->mlx_window);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '1')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->textures.floor, x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->textures.wall, x * tile_size, y * tile_size);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->textures.player, x * tile_size, y * tile_size);
			else if (game->map[y][x] == 'C' && game->textures.collectible)
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->textures.collectible, x * tile_size, y * tile_size);
			else if (game->map[y][x] == 'E' && game->textures.exit)
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->textures.exit, x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int			y;
	int			x;
	int			current_x = 0, current_y;
	static int	move_count = 0;
	int			new_x;
	int			new_y;

	y = 0;
	current_x = 0, current_y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				current_x = x;
				current_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
	new_x = current_x + dx;
	new_y = current_y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'E')
	{
		if (!check_all_collected(game))
			return ;
		ft_printf("Moves : %d\n", move_count + 1);
		ft_printf("You won!\n");
		close_window(game);
	}
	game->map[current_y][current_x] = '0';
	game->map[new_y][new_x] = 'P';
	move_count++;
	ft_printf("Moves: %d\n", move_count);
	render_map(game);
}

int	check_all_collected(t_game *game)
{
	for (int y = 0; game->map[y]; y++)
	{
		for (int x = 0; game->map[y][x]; x++)
		{
			if (game->map[y][x] == 'C')
				return (0);
		}
	}
	return (1);
}