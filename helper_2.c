/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:18:32 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:16:30 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}

void	error(const char *s)
{
	perror((char *)s);
}

int	count_lines(const char *Pathname_map)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(Pathname_map, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
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
int	key_handler(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 65362)
		move_player(game, 0, -1);
	else if (keycode == 97 || keycode == 65361)
		move_player(game, -1, 0);
	else if (keycode == 115 || keycode == 65364)
		move_player(game, 0, 1);
	else if (keycode == 100 || keycode == 65363)
		move_player(game, 1, 0);
	else if (keycode == 65307)
		return (close_window(game));
	return (0);
}
