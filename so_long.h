/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/03/14 03:01:17 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_len/get_next_line.h"
#include "mlx.h"

typedef struct s_game
{
    void    *mlx; 
    int     win_x;
    int     win_y;
    char    **map;
    void    *mlx_win
}t_game;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

char **parse_map(const char *Pathname_map, t_game *game);
int check_shape(char **map);
int check_walls(char **map);
int check_player(char **map);
int check_map(char **map);

void ERROR(const char *s);
int count_lines(const char *Pathname_map);


# endif
