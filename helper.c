/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:48 by salhali           #+#    #+#             */
/*   Updated: 2025/03/12 23:18:24 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ERROR(const char *s)
{
        perror((char *)s);
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
    return count;// function return count = 6 3la 7ssab map 3ndi fiha 6 col 
}