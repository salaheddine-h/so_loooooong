/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/04/10 20:48:31 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./ft_printf/ft_printf.h"
# include "./get_len/get_next_line.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifdef __linux__
# endif

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*collectible;
	void		*exit;
}				t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*img;
	void		*mlx_window;
	int			win_x;
	int			win_y;
	char		**map;
	char		**cpy_map;
	t_textures	textures;
}				t_game;

typedef struct s_data
{
	void		*img_window;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

// -------------> main
void			init_game_struct(t_game *game);
void			free_map_and_copy(t_game *game);
int				check_valid_map_and_path(t_game *game);
int				create_window_and_image(t_game *game, t_data *img, int size);
int				init_graphics(t_game *game, t_data *img);
void			setup_hooks_and_loop(t_game *game);

// -------------> check_parsing

int				check_player(char **map);
int				is_map_valid_elements(int p, int e, int c);
void			count_elements(char **map, int *p_count, int *e_count,
					int *c_count);

// -------------> map_parsing

char			**parse_map(const char *Pathname_map, t_game *game);
int				check_shape(char **map);
int				check_map(char **map);

// -------------> check_walls
void			get_map_size(char **map, size_t *width, size_t *height);
int				check_horizontal_walls(char **map, size_t width, size_t height);
int				sanitize_and_check_vertical_walls(char **map, size_t height);
int				check_walls(char **map);

// -------------> cpy_map

char			**copy_map(char **origin_map);
size_t			double_str_len(char **str);

// -------------> load_game

int				load_textures(t_game *game);
void			render_floor(t_game *game, int tile_size);
void			render_map(t_game *game);
void			render_objects(t_game *game, int tile_size);
void			move_player(t_game *game, int dx, int dy);
int				check_all_collected(t_game *game);
int				find_player_pos(t_game *game, int *x_pos, int *y_pos);

// -------------> helper_1

int				check_all_collected(t_game *game);
void			flood_fill(char **map, int x, int y);
int				validate_path(t_game *game);
int				find_player_position(t_game *game, int *player_x,
					int *player_y);
int				check_unreachable_elements(char **map);

// -------------> helper_2

int				key_handler(int keycode, t_game *game);
void			*ft_memset(void *s, int c, size_t n);
int				count_lines(const char *Pathname_map);
void			error(char *s);
int				close_window(t_game *game);

// -------------> cleanning

void			free_textures(t_game *game);
void			free_window(t_game *game);
void			free_map(char **map);
void			free_mlx(t_game *game);
void			cleanup(t_game *game);
char			*ft_strtrim(char *s1, char *set);
void			check_dotber(char **av);

#endif
