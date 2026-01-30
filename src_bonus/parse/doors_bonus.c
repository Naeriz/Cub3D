/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:06:37 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/30 18:17:11 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	is_valid_door_position(t_map *data, int x, int y)
{
	int	vertical;
	int	horizontal;

	horizontal = (get_char_safe(data, x - 1, y) == '1')
		&& (get_char_safe(data, x + 1, y) == '1');
	vertical = (get_char_safe(data, x, y - 1) == '1')
		&& (get_char_safe(data, x, y + 1) == '1');
	if (horizontal || vertical)
		return (1);
	return (0);
}

int	check_doors(t_map *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
			{
				if (!is_valid_door_position(data, x, y))
				{
					printf("Error\n Invalid door at x:%d, y:%d\n", x, y);
					return (1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}
