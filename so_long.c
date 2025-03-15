/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/03/15 02:17:27 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"
// #include "mlx.h"
// #include <string.h>

// // int		my_mlx_pixel_put(void *mlx_ptr, int x, int y, int color)
// // {
// //     if(!mlx_ptr)
// //         return(NULL);

// // }
// int main(int ac, char **av)
// {
//     t_game game;
//     t_data  img;
//     int i;

//     if (ac > 2)
//         return (-1);
//     memset(&game,0,sizeof(game));
//     game.map = parse_map(av[1],&game);
//     if (!game.map)
//     {
//         ERROR("ERROR, Empty Map");
//         return (1);
//     }
//     if(!check_map(game.map))
//     {
//         i = 0;
//         while (game.map[i])
//             free(game.map[i++]);
//         free(game.map);
//         return(1);
//     }
//     game.mlx = mlx_init();
//     game.mlx_window = mlx_new_window(game.mlx, game.win_x * 128, game.win_y * 128, "man7wa");
//     img.img_window = mlx_new_image(game.mlx,  game.win_y * 128, game.win_y * 128);
//     img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);
//     mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//     // mlx_string_put(game.mlx, void *win_ptr, int x, int y, int color, char *string);
//     mlx_put_image_to_window(game.mlx, game.mlx_window, img.img_window, 0, 0);
//     mlx_loop(game.mlx);
//     return (0);
// }

// // int	main(void)
// // {
// // 	void	*mlx;
// // 	void	*mlx_win;
// // 	t_data	img;

// // 	mlx = mlx_init();
// // 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// // 	img.img = mlx_new_image(mlx, 1920, 1080);
// // 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// // 								&img.endian);
// // 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// // 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// // 	mlx_loop(mlx);
// // }


#include "so_long.h"
// #include "mlx.h"
#include <string.h>

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

int key_handler(int keycode, t_game *game)
{
    if (keycode == 65307)
        close_window(game);
    return (0);
}

int main(int ac, char **av)
{
    t_game game;
    t_data img;
    int i;

    if (ac != 2)
    	ft_error_message("Error input", 1);
    ft_memset(&game, 0, sizeof(game));
    // ft_init_values(&game);
    game.map = parse_map(av[1], &game);

    if (!game.map)
	    ft_error_message("Error : emty map", 1);
    if(!check_map(game.map))
    {
        i = 0;
        while (game.map[i])
            free(game.map[i++]);
        free(game.map);
        return(1);
    }

    game.mlx = mlx_init();
    if (!game.mlx)
    	exit(EXIT_FAILURE);
    game.mlx_window = mlx_new_window(game.mlx, game.win_x * 30, game.win_y * 80, "Man7waaa");
    if (!game.mlx_window)
    {
        ERROR("Error : Window creation failed");
        free(game.mlx);
        return (1);
    }

    img.img_window = mlx_new_image(game.mlx, game.win_x * 128, game.win_y * 128);
    if (!img.img_window)
    {
        ERROR("Error : Image creation failed");
        mlx_destroy_window(game.mlx, game.mlx_window);
        free(game.mlx);
        return (1);
    }
    img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Add code to load textures here

    // Add code to render the initial map here

    // Set up event hooks
    mlx_key_hook(game.mlx_window, key_handler, &game);
    mlx_hook(game.mlx_window, 17, 0, close_window, &game); // For window close button

    mlx_loop(game.mlx);
    // return (0);
}
