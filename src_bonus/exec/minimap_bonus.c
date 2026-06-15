/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:38:37 by sionow            #+#    #+#             */
/*   Updated: 2026/02/09 02:23:34 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	draw_grid(t_map *data, int x, int y, int color)
{
	int	ht;
	int	wd;
	int	i;
	int	j;

	i = 0;
	ht = 200 / data->height;
	wd = 200 / data->width;
	if (x * wd >= 200 || y * ht >= 200)
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
				else if (data->map[y][x] == '1' || data->map[y][x] == ' ')
					color = data->textures->floor;
			}
			if (color != -1)
				draw_grid(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_mlx *mlx, t_map *d, int x, int y)
{
	uint32_t	*pixels;
	int			i;
	int			j;
	uint32_t	color;
	int			scale;

	if (d->north == 1)
		pixels = (uint32_t *)mlx->oia1_adr;
	else
		pixels = (uint32_t *)mlx->oia2_adr;
	scale = 2;
	i = 0;
	while (i < 64 / scale && (y + i) < 200)
	{
		j = 0;
		while (j < 64 / scale && (x + j) < 200)
		{
			color = pixels[(i * scale) * (d->line_b / 4) + (j * scale)];
			if ((color & 0xFF000000) == 0)
				my_mlx_pixel_put(d, x + j, y + i, color);
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
	int	icon_size;

	height = 200 / data->height;
	width = 200 / data->width;
	draw_map(data);
	icon_size = 32;
	p_x = (data->player_x * width) - (icon_size / 2);
	p_y = (data->player_y * height) - (icon_size / 2);
	if (p_x < 3)
		p_x = 3;
	if (p_y < 3)
		p_y = 3;
	if (p_x + icon_size > 189)
		p_x = 189 - icon_size;
	if (p_y + icon_size > 189)
		p_y = 189 - icon_size;
	draw_player(&data->mlx, data, p_x, p_y);
}
