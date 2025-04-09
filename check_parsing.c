/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:30:42 by salhali           #+#    #+#             */
/*   Updated: 2025/04/09 20:31:13 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_player(char **map)
{
	int	count_p;
	int	count_e;
	int	count_c;

	count_p = 0;
	count_e = 0;
	count_c = 0;
	count_elements(map, &count_p, &count_e, &count_c);
	return (is_map_valid_elements(count_p, count_e, count_c));
}
int	is_map_valid_elements(int p, int e, int c)
{
	if (p == -1)
		return (0);
	if (p != 1 || e != 1 || c < 1)
		return (0);
	return (1);
}

void	count_elements(char **map, int *p_count, int *e_count, int *c_count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				(*p_count)++;
			else if (map[i][j] == 'E')
				(*e_count)++;
			else if (map[i][j] == 'C')
				(*c_count)++;
			else if (map[i][j] != '0' && map[i][j] != '1')
			{
				*p_count = -1; // signal for error
				return ;
			}
			j++;
		}
		i++;
	}
}
