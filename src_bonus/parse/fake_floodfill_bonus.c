/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_floodfill_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:52:31 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/08 13:38:08 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

char	get_char_safe(t_map *data, int x, int y)
{
	if (y < 0 || y >= data->height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (' ');
	return (data->map[y][x]);
}

int	is_enclosed(t_map *data, int x, int y)
{
	if (get_char_safe(data, x, y - 1) == ' '
		|| get_char_safe(data, x, y + 1) == ' '
		|| get_char_safe(data, x - 1, y) == ' '
		|| get_char_safe(data, x + 1, y) == ' ')
		return (1);
	return (0);
}

int	check_walls(t_map *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("0NSEW", data->map[y][x]))
			{
				if (is_enclosed(data, x, y))
				{
					printf("Error\n map is not enclosed at x: %d, y: %d\n",
						x, y);
					return (1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}
