/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:28:44 by salhali           #+#    #+#             */
/*   Updated: 2025/03/12 23:17:54 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_len/get_next_line.h"

///-----map_parsing-----////

int count_lines(const char *Pathname_map);
char **parse_map(const char *Pathname_map);
int check_shape(char **map);
int check_walls(char **map);
int check_player(char **map);
int check_map(char **map);

/// -----Helper----// 

size_t ft_strlen(char *str);
void ERROR(const char *s);


# endif
