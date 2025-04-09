/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:54:09 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
}

void	free_map_and_copy(t_game *game)
{
	int	i;

	i = 0;
	while (game->map && game->map[i])
		free(game->map[i++]);
	free(game->map);
	i = 0;
	while (game->cpy_map && game->cpy_map[i])
		free(game->cpy_map[i++]);
	free(game->cpy_map);
}

int	check_valid_map_and_path(t_game *game)
{
	if (!(check_map(game->map)) || !validate_path(game))
	{
		free_map_and_copy(game);
		error("Error: Invalid map path");
		return (0);
	}
	return (1);
}

int	create_window_and_image(t_game *game, t_data *img, int size)
{
	game->mlx_window = mlx_new_window(game->mlx, game->win_x * size, game->win_y
			* size, "Man7waaa");
	if (!game->mlx_window)
	{
		error("Error: Window creation failed");
		cleanup(game);
		return (0);
	}
	img->img_window = mlx_new_image(game->mlx, game->win_x * size, game->win_y
			* size);
	if (!img->img_window)
	{
		error("Error: Image creation failed");
		cleanup(game);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img_window, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	game->img = img->img_window;
	return (1);
}

int	init_graphics(t_game *game, t_data *img)
{
	int	size;

	size = 64;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	if (!create_window_and_image(game, img, size))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_data	img;

	if (ac != 2)
		error("Error input");
	init_game_struct(&game);
	game.map = parse_map(av[1], &game);
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
	return (0);
}
