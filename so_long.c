/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:59:39 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_hooks_and_loop(t_game *game)
{
	mlx_hook(game->mlx_window, 17, 0, close_window, game);
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_handler, game);
	mlx_key_hook(game->mlx_window, key_handler, game);
	mlx_loop(game->mlx);
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
