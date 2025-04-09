/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 17:21:35 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./get_len/get_next_line.h"
#include "./ft_printf/ft_printf.h"
#include "mlx.h"


typedef struct s_textures
{
    void *wall;
    void *floor;
    void *player;
    void *collectible;
    void *exit;
} t_textures;

typedef struct s_game
{
    void	*mlx; // mlx_all_function_hna
    void	*img;
    void	*mlx_window;
    int     win_x; //touL 
    int     win_y; // l3ard 
    char    **map; // map hna 
    char    **cpy_map;
    t_textures textures;
}t_game;


typedef struct	s_data
{
	void	*img_window;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

char **parse_map(const char *Pathname_map, t_game *game);
void	*ft_memset(void *s, int c, size_t n);
int check_shape(char **map);
int check_walls(char **map);
int check_player(char **map);
int check_map(char **map);
void ERROR(const char *s);
int count_lines(const char *Pathname_map);

// Utl__!

int load_textures(t_game *game);
void render_map(t_game *game);
int close_window(t_game *game);
int key_handler(int keycode, t_game *game);
void move_player(t_game *game, int dx, int dy);
int check_all_collected(t_game *game);


void    flood_fill(char **map, int x, int y);
int     validate_path(t_game *game);

void cleanup(t_game *game);


# endif