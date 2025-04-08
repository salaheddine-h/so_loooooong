/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/04/08 13:02:56 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <string.h>

// // // // int		my_mlx_pixel_put(void *mlx_ptr, int x, int y, int color)
// // // // {
// // // //     if(!mlx_ptr)
// // // //         return(NULL);

// // // // }
// // // int main(int ac, char **av)
// // // {
// // //     t_game game;
// // //     t_data  img;
// // //     int i;

// // //     if (ac > 2)
// // //         return (-1);
// // //     memset(&game,0,sizeof(game));
// // //     game.map = parse_map(av[1],&game);
// // //     if (!game.map)
// // //     {
// // //         ERROR("ERROR, Empty Map");
// // //         return (1);
// // //     }
// // //     if(!check_map(game.map))
// // //     {
// // //         i = 0;
// // //         while (game.map[i])
// // //             free(game.map[i++]);
// // //         free(game.map);
// // //         return(1);
// // //     }
// // //     game.mlx = mlx_init();
// // //     game.mlx_window = mlx_new_window(game.mlx, game.win_x * 128, game.win_y * 128, "man7wa");
// // //     img.img_window = mlx_new_image(game.mlx,  game.win_y * 128, game.win_y * 128);
// // //     img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);
// // //     mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// // //     // mlx_string_put(game.mlx, void *win_ptr, int x, int y, int color, char *string);
// // //     mlx_put_image_to_window(game.mlx, game.mlx_window, img.img_window, 0, 0);
// // //     mlx_loop(game.mlx);
// // //     return (0);
// // // }

// // // // int	main(void)
// // // // {
// // // // 	void	*mlx;
// // // // 	void	*mlx_win;
// // // // 	t_data	img;

// // // // 	mlx = mlx_init();
// // // // 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// // // // 	img.img = mlx_new_image(mlx, 1920, 1080);
// // // // 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// // // // 								&img.endian);
// // // // 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// // // // 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// // // // 	mlx_loop(mlx);
// // // // }


// #include "so_long.h"
// // #include "mlx.h"
// // #include <string.h>

int close_window(t_game *game)
{
    int i = 0;

    while (game->map && game->map[i])
        free(game->map[i++]);
    free(game->map);
    if (game->mlx_window)
        mlx_destroy_window(game->mlx, game->mlx_window);
    free(game->mlx);
    exit(0);
    return (0);
}
int load_textures(t_game *game)
{
    int width, height;

    // // Load floor texture
    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm", &width, &height);
    if (!game->textures.floor)
        return (0);
    // Load player texture
    game->textures.player = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &width, &height);
    if (!game->textures.player)
        return (0);
    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &width, &height);
    if (!game->textures.wall)
        return(0);
    // game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "/home/salhali/Desktop/char", &width, &height);
    // if (!game->textures.collectible)
    //     return (0);
    game->textures.exit = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm", &width, &height);
    if (!game->textures.exit)
        return (0);
    return (1);
}


void render_map(t_game *game)
{
    int x, y;
    int tile_size = 64;

    y = 0;
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
            // else if (game->map[y][x] == 'C' && game->textures.collectible)
            //     mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.collectible, x * tile_size, y * tile_size);
            // else if (game->map[y][x] == 'E' && game->textures.exit)
            //     mlx_put_image_to_window(game->mlx, game->mlx_window, game->textures.exit, x * tile_size, y * tile_size);
            x++;
        }
        y++;
    }
}

int key_handler(int keycode, t_game *game)
{
    // W or up arrow - move up
    if (keycode == 119 || keycode == 65362)
        move_player(game, 0, -1);
    // A or left arrow - move left
    else if (keycode == 97 || keycode == 65361)
        move_player(game, -1, 0);
    // S or down arrow - move down
    else if (keycode == 115 || keycode == 65364)
        move_player(game, 0, 1);
    // D or right arrow - move right
    else if (keycode == 100 || keycode == 65363)
        move_player(game, 1, 0);
    // ESC key to exit
    else if (keycode == 65307)
        return close_window(game);

    return (0);
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
    // printf("something happend\n");
    int new_x = current_x + dx;
    int new_y = current_y + dy;
    // Check if move is valid
    if (game->map[new_y][new_x] == '1')
        return;

    if (game->map[new_y][new_x] == 'C') {
        // Collect item logic
        // You might want to increment a counter here
    }

    // Check for exit
    if (game->map[new_y][new_x] == 'E')
    {
        // Check if all collectibles are collected
        // If yes, end the game
        // If not, just return and don't move
        if (!check_all_collected(game))
            return;

        printf("You won! Moves: %d\n", move_count + 1);
        close_window(game);
    }

    // Move player
    game->map[current_y][current_x] = '0';
    game->map[new_y][new_x] = 'P';

    move_count++;
    printf("Moves: %d\n", move_count);

    // Redraw map
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

int main(int ac, char **av)
{
    t_game game;
    t_data img;
    int i;

    if (ac != 2)
    	ERROR("Error input");
    ft_memset(&game, 0, sizeof(game));
    game.map = parse_map(av[1], &game);
    if (game.map != NULL)
    {
	    if(!(check_map(game.map)))
	    {
		    i = 0;
		    while(game.map[i])
			    free(game.map[i++]);
		    free(game.map);
		    return(1);
	    }
    }
    game.mlx = mlx_init();
    if (!game.mlx)
    	exit(EXIT_FAILURE);
    int size = 64;
    game.mlx_window = mlx_new_window(game.mlx, game.win_x * size, game.win_y * size, "Man7waaa");
    if (!game.mlx_window)
    {
        ERROR("Error : Window creation failed");
        free(game.mlx);
        return (1);
    }
    img.img_window = mlx_new_image(game.mlx, game.win_x * size, game.win_y * size);
    if (!img.img_window)
    {
        ERROR("Error : Image creation failed");
        mlx_destroy_window(game.mlx, game.mlx_window);
        free(game.mlx);
        return (1);
    }
    img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);
    game.img = img.img_window;
    if(!load_textures(&game))
    {
        mlx_destroy_image(game.mlx, img.img_window);
        mlx_destroy_window(game.mlx, game.mlx_window);
        free(game.mlx);
        i = 0;
        while(game.map[i])
            free(game.map[i++]);
        free(game.map);
        return(1);
    }
    render_map(&game);
    mlx_key_hook(game.mlx_window, key_handler, &game);
    // mlx_hook(game.mlx_window, 17, 0, close_window, &game);
    mlx_loop(game.mlx);
    return (0);
}


// int main(int ac, char **av) {
//     t_game game;
//     t_data img;
//     int i;

//     if (ac != 2)
//         ft_error_message("Error input", 1);

//     ft_memset(&game, 0, sizeof(game));
//     game.map = parse_map(av[1], &game);
//     if (game.map != NULL) {
//         if(!(check_map(game.map)))
//         {
//             i = 0;
//             while(game.map[i])
//                 free(game.map[i++]);
//             free(game.map);
//             return(1);
//         }
//     }
//     game.mlx = mlx_init();
//     if (!game.mlx)
//         exit(EXIT_FAILURE);
//     int tile_size = 64;
//     game.mlx_window = mlx_new_window(game.mlx, game.win_x * tile_size, game.win_y * tile_size, "Man7waaa");
//     if (!game.mlx_window) {
//         ERROR("Error : Window creation failed");
//         free(game.mlx);
//         return (1);
//     }
//     img.img_window = mlx_new_image(game.mlx, game.win_x * tile_size, game.win_y * tile_size);
//     if (!img.img_window) {
//         ERROR("Error : Image creation failed");
//         mlx_destroy_window(game.mlx, game.mlx_window);
//         free(game.mlx);
//         return (1);
//     }
//     img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);
//     game.img = img.img_window;
//     if (!load_textures(&game)) {
//         mlx_destroy_image(game.mlx, img.img_window);
//         mlx_destroy_window(game.mlx, game.mlx_window);
//         free(game.mlx);
//         return (1);
//     }
//     render_map(&game);
//     mlx_key_hook(game.mlx_window, key_handler, &game);
//     mlx_hook(game.mlx_window, 17, 0, close_window, &game);
//     mlx_loop(game.mlx);
//     return (0);
// }
