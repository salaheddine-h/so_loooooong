/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/04/07 14:31:34 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # ifndef SO_LONG_H
// # define SO_LONG_H

// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include "./get_len/get_next_line.h"
// // #include "./minilibx-linux/mlx.h"
// #include "mlx.h"

// typedef struct s_game
// {
//     void	*mlx;
//     void	*img;
//     void	*mlx_window;
//     int     win_x;
//     int     win_y;
//     char    **map;
//     char    **cpy_map;
// 	t_textures textures;

// }t_game;


// typedef struct	s_data
// {
// 	void	*img_window; //
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	// t_textures textures;
// }t_data;


// typedef struct s_textures
// {
//     void *wall;
//     void *floor;
//     void *player;
//     void *collectible;
//     void *exit;
// } t_textures;

// // Then add to t_game:
// // t_textures textures;
// char **parse_map(const char *Pathname_map, t_game *game);
// void	*ft_memset(void *s, int c, size_t n);
// int check_shape(char **map);
// int check_walls(char **map);
// int check_player(char **map);
// int check_map(char **map);
// void	ft_error_message(char *str, int error);
// void ERROR(const char *s);
// int count_lines(const char *Pathname_map);
// int close_window(t_game *game);
// int key_handler(int keycode, t_game *game);
// int load_textures(t_game *game);
// void render_map(t_game *game);


// # endif

# ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./get_len/get_next_line.h"
#include "./minilibx-linux/mlx.h"
// #include "mlx.h"


typedef struct s_textures
{
    void *wall; //here
    void *floor;
    void *player;
    void *collectible;
    void *exit;
} t_textures;

typedef struct s_game
{
    void	*mlx;
    void	*img;
    void	*mlx_window;
    int     win_x;
    int     win_y;
    char    **map;
    char    **cpy_map;
    t_textures textures;  // This is now properly defined
}t_game;



typedef struct	s_data
{
	void	*img_window; //
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
// void	ft_error_message(char *str, int error);
void ERROR(const char *s);
int count_lines(const char *Pathname_map);

// Utl__!
int load_textures(t_game *game);
void render_map(t_game *game);
int close_window(t_game *game);
int key_handler(int keycode, t_game *game);
void move_player(t_game *game, int dx, int dy);
int check_all_collected(t_game *game);


# endif