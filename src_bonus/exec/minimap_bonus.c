/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:38:37 by sionow            #+#    #+#             */
/*   Updated: 2026/01/02 19:33:35 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

//have to put pixel by pixel so disgusting shit
void	draw_grid(t_map *data, int x, int y, int color)
{
	int ht;
	int wd;
	int	i;
	int	j;

	i = 0;
	ht = 200 / data->height;
	wd = 200 / data->width;
	if (x * wd >= 200 || y * ht >= 200) //multiplied to not draw out of bounds
		return ;
	while (i < ht)
	{
		j = 0;
		while (j < wd)
		{
			if ((x * wd) + j < 200 && (y * ht) + i < 200)
				my_mlx_pixel_put(data, (x * wd) + j, (y * ht) + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_map *data)
{
	int	x;
	int	y;
	int	color;
	
	y = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			color = -1;
			if (y < data->height && x < (int)ft_strlen(data->map[y]))
			{
				if (data->map[y][x] == '0' || data->map[y][x] > 50)
					color = 0xFFFFFF;
				else if (data->map[y][x] == '1')
					color = data->textures->floor;
			}
			if (color != -1)
				draw_grid(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_map *data, int x, int y)
{
	int	i; //both for dotsize
	int	j;

	i = 0;
	while (i <= 4)
	{
		j = 0;
		while(j <= 4)
		{
			if (x + i < 200 && y + j < 200)
				my_mlx_pixel_put(data, x + i, y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	init_minimap(t_map *data)
{
	int	p_x;
	int	p_y;
	int	height;
	int	width;

	height = 200 / data->height;
	width = 200 / data->width;
	draw_map(data);
	p_x = (data->player_x * width) - 3;
	p_y = (data->player_y * height) - 3;
	draw_player(data, p_x, p_y);
}
