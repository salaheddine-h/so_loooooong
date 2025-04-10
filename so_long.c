/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/04/10 20:55:01 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_hooks_and_loop(t_game *game)
{
	mlx_hook(game->mlx_window, 17, 0, close_window, game);
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_handler, game);
	mlx_loop(game->mlx);
}

void	render_floor(t_game *game, int tile_size)
{
	int	x;
	int	y;

	y = 0;
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
}

void	render_objects(t_game *game, int tile_size)
{
	int	x;
	int	y;

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

void	render_map(t_game *game)
{
	int	tile_size;

	tile_size = 64;
	mlx_clear_window(game->mlx, game->mlx_window);
	render_floor(game, tile_size);
	render_objects(game, tile_size);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_data	img;

	if (ac != 2)
		error("Error input");
	check_dotber(av);
	init_game_struct(&game);
	game.map = parse_map(av[1], &game);
	if ((game.win_x * 64 >= 3848) || (game.win_y * 64 >= 2160))
			return (0);
	if (!game.map || !check_valid_map_and_path(&game))
		return (1);
	if (!init_graphics(&game, &img))
		return (1);
	if (!load_textures(&game))
	{
		cleanup(&game);
		return (1);
	}
	render_map(&game);
	setup_hooks_and_loop(&game);
	cleanup(&game);
}
