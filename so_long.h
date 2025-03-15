/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/03/15 02:17:13 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./get_len/get_next_line.h"
#include "./minilibx-linux/mlx.h"

typedef struct s_game
{
    void    *mlx;
    int     win_x;
    int     win_y;
    char    **map;
		char    **cpy_map;
    void    *mlx_window;
}t_game;


typedef struct	s_data
{
	void	*img_window;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;


// Thia function initialize the values with NULL.
/*void	ft_init_values(t_game *game)
{
	game->mapall = NULL;
	game->wall = NULL;
	game->exit = NULL;
	game->item = NULL;
	game->player = NULL;
	game->space = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->width = 0;
	game->height = 0;
	game->players = 0;
	game->gameover = 0;
	game->steps = 0;
	game->score = 0;
	game->max_score = 0;
}*/
char **parse_map(const char *Pathname_map, t_game *game);
void	*ft_memset(void *s, int c, size_t n);
int check_shape(char **map);
int check_walls(char **map);
int check_player(char **map);
int check_map(char **map);
void	ft_error_message(char *str, int error);
void ERROR(const char *s);
int count_lines(const char *Pathname_map);


# endif
