/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/03/14 08:58:52 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <string.h>

int main(int ac, char **av)
{
    t_game game;
    t_data  img;
    int i;

    if (ac > 2)
        return (-1); 
    memset(&game,0,sizeof(game));
    game.map = parse_map(av[1],&game);
    if (!game.map)
    {
        ERROR("ERROR, Empty Map");
        return (1);
    }
    if(!check_map(game.map))
    {
        i = 0;
        while (game.map[i])
            free(game.map[i++]);
        free(game.map);
        return(1);
    }
    printf("spam");
    game.mlx = mlx_init();
    game.mlx_win = mlx_new_window(game.mlx, game.win_x * 128, game.win_y * 128, "man7wa");
    img.img = mlx_new_image(game.mlx,  game.win_y * 128, game.win_y * 128);
    
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_loop(game.mlx);
    return (0);
}

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }