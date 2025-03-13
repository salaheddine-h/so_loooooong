/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:42:03 by salhali           #+#    #+#             */
/*   Updated: 2025/03/13 00:53:52 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(void)
{
    char **map;
    int i;

    map = parse_map("map.ber");
    if (!map)
    {
        ERROR("ERROR, Empty Map");
        return (1);
    }
    if(!check_map(map))
    {
        free(map);
        return(1);
    }
    i = 0;
    while (map[i])
    {
        printf("%s", map[i]);
        free(map[i]);
        i++;
    }
    write(1, "\nMAP_N9IIYA\n", 13);
    printf("%s", "\U0001F96B\U0001F96B\U0001F96B\U0001F96B\U0001F96B\n");
    free(map);
    return (0);
}