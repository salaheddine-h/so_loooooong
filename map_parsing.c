/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:17:05 by salhali           #+#    #+#             */
/*   Updated: 2025/03/14 02:41:26 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **parse_map(const char *Pathname_map, t_game *game)
{
    int     fd;
    int     total_lines;
    int     i;
    char    **map;
    total_lines = count_lines(Pathname_map);
    if (total_lines <= 0)
        return NULL;
    
    map = malloc(sizeof(char *) * (total_lines + 1));
    if (!map)
        return NULL;
    
    fd = open(Pathname_map, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    i = 0;
    while ((map[i] = get_next_line(fd)) != NULL)
        i++;
    map[i] = NULL;
    close(fd);
    game->win_x = i; // 6
    game->win_y = ft_strlen(map[0]); // 34
    return map;
}

int check_shape(char **map)
{
    size_t i;
    size_t len;
    size_t  curr_len;

    if (!map || !map[0])
        return 0;
    len = ft_strlen(map[0]);
    if(map[0][len - 1] == '\n')
        len--;
    i = 1;
    while (map[i])
    {
        curr_len = ft_strlen(map[i]);
        if (map[i][curr_len - 1] == '\n')
            curr_len--;
        if (curr_len != len)
            return 0;
        i++;
    }
    return 1;
}

int check_walls(char **map) //Walls الجدران
{
    size_t i;
    size_t  j;
    size_t count_Y = 0;
    size_t  count_X;
    size_t  current_len;

    while (map[count_Y])
        count_Y++;
    count_X = ft_strlen(map[0]);
    if(map[0][count_X - 1] == '\n')
        count_X--;
    j = 0;
    while(j < count_X)
    {
        if(map[0][j] != '1' || map[count_Y - 1][j] != '1')
            return 0;
        j++;
    }
    i = 0;
    while(i < count_Y )
    {
        current_len = ft_strlen(map[i]);
        if(map[i][current_len - 1] == '\n')
        {
            map[i][current_len - 1] = 0;
            current_len--;
        }
        if(map[i][0] != '1' || map[i][current_len - 1] != '1')
            return 0;
        i++;
    }
    return 1;
}

int check_player(char **map)
{
    int i;
    int j;
    int count_player = 0;
    int count_exit = 0;
    int count_collectible = 0;

    i = 0;
    while(map[i] != NULL)
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'P')
                count_player++;
            else if(map[i][j] == 'E')
                count_exit++;
            else if(map[i][j] == 'C')
                count_collectible++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return 0;
            j++;
        }
        i++;
    }
    // printf("count player[%d], exit[%d] , coints[%d]\n",count_player, count_exit, count_collectible);
    if(count_player != 1 || count_exit != 1 || count_collectible < 1)
        return 0;
    return 1;
}

int check_map(char **map)
{
    if (check_shape(map) == 0)//Shape شكل
    {
        ERROR("Error: Map is not valid.\n");
        return 0;
    }
    if (check_walls(map) == 0) //Walls الجدران
    {
        ERROR("Error: Map Walls are not valid.\n");
        return 0;
    }
    if (check_player(map) == 0) //Valid Characters P C E 1 0 ou khassni enmy
    {
        ERROR("Error: Map does not contain required player.\n");
        return 0;
    }
    return 1;
}

