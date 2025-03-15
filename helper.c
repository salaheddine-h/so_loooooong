/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:41:48 by salhali           #+#    #+#             */
/*   Updated: 2025/03/15 02:17:01 by salah            ###   ########.fr       */
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
void	ft_error_message(char *str, int error)
{
	if(!str)
	{
		printf("Error : ./so_long");
	}
	else
	{
		write(2, "Error\n", 7);
		printf("%s", str);
	}
	(void)error;
	exit(error);
}
