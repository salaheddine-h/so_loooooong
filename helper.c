/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:48 by salhali           #+#    #+#             */
/*   Updated: 2025/04/08 19:02:05 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ERROR(const char *s)
{
        perror((char *)s);
}
void flood_fill(char **map, int x, int y)
{
    if (map[y][x] == '1' || map[y][x] == 'X')
        return;
    
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
    
    // First, find the player's position
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
    
    // Start flood fill from player position
    flood_fill(game->cpy_map, player_x, player_y);
    
    // Check if all collectibles and exit are reachable
    y = 0;
    while (game->cpy_map[y])
    {
        x = 0;
        while (game->cpy_map[y][x])
        {
            // If we find a collectible or exit that hasn't been 
            // replaced with 'X', it means it's unreachable
            if (game->cpy_map[y][x] == 'C' || game->cpy_map[y][x] == 'E')
                return (0);
            x++;
        }
        y++;
    }
    
    return (1); // All collectibles and exit are reachable
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

