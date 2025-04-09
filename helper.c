/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:48 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 16:35:43 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ERROR(const char *s)
{
        perror((char *)s);
}
void flood_fill(char **map, int x, int y)
{
    if (map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'X')
    {
        if (map[y][x] == 'E')
            map[y][x] = '1';
        return;
    }
    
    map[y][x] = 'X';
    
    flood_fill(map, x + 1, y); // Right
    flood_fill(map, x - 1, y); // Left
    flood_fill(map, x, y + 1); // Down
    flood_fill(map, x, y - 1); // Up
}

int validate_path(t_game *game)
{
    int player_x = -1, player_y = -1;
    int y = 0, x;
    
    while (game->cpy_map[y])
    {
        x = 0;
        while (game->cpy_map[y][x])
        {
            if (game->cpy_map[y][x] == 'P')
            {
                player_x = x;
                player_y = y;
                break;
            }
            x++;
        }
        if (player_x != -1)
            break;
        y++;
    }
    
    flood_fill(game->cpy_map, player_x, player_y);
    
    y = 0;
    while (game->cpy_map[y])
    {
        x = 0;
        while (game->cpy_map[y][x])
        {
            if (game->cpy_map[y][x] == 'C' || game->cpy_map[y][x] == 'E')
                return (0);
            x++;
        }
        y++;
    }
    
    return (1);
}

int count_lines(const char *Pathname_map)
{
    int fd;
    int count = 0;
    char *line;

    fd = open(Pathname_map, O_RDONLY);
    if (fd == -1)
        return -1;
    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
    }
    close(fd);
    return count;
}
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// int close_window(t_game *game)
// {
//     cleanup(game);
//     exit(0);
//     return (0);
// }

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
// void cleanup(t_game *game)
// {
//     int i = 0;
    
//     // Free textures
//     if (game->textures.floor)
//         mlx_destroy_image(game->mlx, game->textures.floor);
//     if (game->textures.player)
//         mlx_destroy_image(game->mlx, game->textures.player);
//     if (game->textures.wall)
//         mlx_destroy_image(game->mlx, game->textures.wall);
//     if (game->textures.collectible)
//         mlx_destroy_image(game->mlx, game->textures.collectible);
//     if (game->textures.exit)
//         mlx_destroy_image(game->mlx, game->textures.exit);
    
//     // Free window resources
//     if (game->img)
//         mlx_destroy_image(game->mlx, game->img);
//     if (game->mlx_window)
//         mlx_destroy_window(game->mlx, game->mlx_window);
    
//     // Free map
//     while (game->map && game->map[i])
//         free(game->map[i++]);
//     if (game->map)
//         free(game->map);
    
//     // Free copy map if exists
//     i = 0;
//     while (game->cpy_map && game->cpy_map[i])
//         free(game->cpy_map[i++]);
//     if (game->cpy_map)
//         free(game->cpy_map);
    
//     // Free MLX connection
//     if (game->mlx)
//         free(game->mlx);
// }
