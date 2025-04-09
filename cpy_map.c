/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:34:11 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:34:24 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	double_str_len(char **str)
{
	size_t	i;

	i = 0;
	while (*str)
		i++, str++;
	return (i);
}
char	**copy_map(char **origin_map)
{
	size_t len;
	int i;
	char **map_copy;

	len = double_str_len(origin_map);
	map_copy = malloc(sizeof(char *) * (len + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (origin_map[i])
	{
		map_copy[i] = ft_strdup(origin_map[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}