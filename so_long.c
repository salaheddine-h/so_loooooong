/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 17:20:56 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int load_textures(t_game *game)
{
    int width, height;

    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm", &width, &height);
    if (!game->textures.floor)
        return (0);
    game->textures.player = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &width, &height);
    if (!game->textures.player)
        return (0);
    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &width, &height);
    if (!game->textures.wall)
        return(0);
    game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "./textures/collectible.xpm", &width, &height);
    if (!game->textures.collectible)
        return (0);
    game->textures.exit = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &width, &height);
    if (!game->textures.exit)
        return (0);
    return (1);
}

void render_map(t_game *game)
{
    int x, y;
    int tile_size;

    y = 0;
    tile_size = 64;
    mlx_clear_window(game->mlx , game->mlx_window);
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] != '1')
                mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.floor, x * tile_size, y * tile_size);
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
                mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.wall, x * tile_size, y * tile_size);
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.player, x * tile_size, y * tile_size);
            else if (game->map[y][x] == 'C' && game->textures.collectible)
                mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.collectible, x * tile_size, y * tile_size);
            else if (game->map[y][x] == 'E' && game->textures.exit)
                mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.exit, x * tile_size, y * tile_size);
            x++;
        }
        y++;
    }
}

void move_player(t_game *game, int dx, int dy)
{
    int y = 0;
    int x;
    int current_x = 0, current_y = 0;
    static int move_count = 0;

    while(game->map[y])
    {
        x = 0;
        while(game->map[y][x])
        {
            if (game->map[y][x] == 'P')
            {
                current_x = x;
                current_y = y;
                break;
            }
            x++;
        }
        y++;
    }
    int new_x = current_x + dx;
    int new_y = current_y + dy;
    if (game->map[new_y][new_x] == '1')
        return;
    if (game->map[new_y][new_x] == 'E')
    {
        if (!check_all_collected(game))
            return;
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

int check_all_collected(t_game *game)
{
    for (int y = 0; game->map[y]; y++) {
        for (int x = 0; game->map[y][x]; x++) {
            if (game->map[y][x] == 'C')
                return 0;
        }
    }
    return 1;
}

void cleanup(t_game *game)
{
    int i = 0;
    
    // Free textures
    if (game->textures.floor)
        mlx_destroy_image(game->mlx, game->textures.floor);
    if (game->textures.player)
        mlx_destroy_image(game->mlx, game->textures.player);
    if (game->textures.wall)
        mlx_destroy_image(game->mlx, game->textures.wall);
    if (game->textures.collectible)
        mlx_destroy_image(game->mlx, game->textures.collectible);
    if (game->textures.exit)
        mlx_destroy_image(game->mlx, game->textures.exit);
    
    // Free window resources
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->mlx_window)
        mlx_destroy_window(game->mlx, game->mlx_window);
    
    // Free map
    while (game->map && game->map[i])
        free(game->map[i++]);
    if (game->map)
        free(game->map);
    
    // Free copy map if exists
    i = 0;
    while (game->cpy_map && game->cpy_map[i])
        free(game->cpy_map[i++]);
    if (game->cpy_map)
        free(game->cpy_map);
    
    // Free MLX connection
    if (game->mlx)
        free(game->mlx);
}

int close_window(t_game *game)
{
    cleanup(game);
    exit(0);
    return (0);
}

int main(int ac, char **av)
{
    t_game game;
    t_data img;
    int i;
    int size;

    if (ac != 2)
    	ERROR("Error input");
    ft_memset(&game, 0, sizeof(game));
    game.map = parse_map(av[1], &game);
    if (game.map != NULL)
    {
	    if(!(check_map(game.map)) || !validate_path(&game))
	    {
		    i = 0;
		    while(game.map[i])
			    free(game.map[i++]);
		    free(game.map);
            i = 0;
            while(game.cpy_map[i])
                free(game.cpy_map[i++]);
            free(game.cpy_map);
            ERROR("Error : Invalid map path - player canat't reach all collectibles or exit");
		    return(1);
	    }
    }
    game.mlx = mlx_init();
    if (!game.mlx)
        exit(EXIT_FAILURE);
    size = 64;
    game.mlx_window = mlx_new_window(game.mlx, game.win_x * size, game.win_y * size, "Man7waaa");
    if (!game.mlx_window)
    {
        ERROR("Error : Window creation failed");
        // free(game.mlx_window);
        cleanup(&game);
        return (1);
    }
    img.img_window = mlx_new_image(game.mlx, game.win_x * size, game.win_y * size);
    if (!img.img_window)
    {
        ERROR("Error : Image creation failed");
        // free(img.img_window);
        cleanup(&game);
        return (1);
    }
    img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);
    game.img = img.img_window;
    if (!load_textures(&game))
    {
        cleanup(&game);
        return(1);
    }
    render_map(&game);
    mlx_hook(game.mlx_window, 17, 0, close_window, &game);
    mlx_key_hook(game.mlx_window, key_handler, &game);
    mlx_loop(game.mlx);
    return (0);
}
