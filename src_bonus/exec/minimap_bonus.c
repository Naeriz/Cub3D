/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:38:37 by sionow            #+#    #+#             */
/*   Updated: 2026/01/11 20:32:05 by sionow           ###   ########.fr       */
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

void	draw_player(t_mlx *mlx, t_map *data, int x, int y)
{
	char		*img_data;
	uint32_t	*pixels;
	int			i;
	int			j;
	uint32_t	color;
	int			bpp;
	int			line_b;
	int			endian;
	int			scale;

	if (data->north == 1)
		img_data = mlx_get_data_addr(mlx->text_oia1, &bpp, &line_b, &endian);
	else
		img_data = mlx_get_data_addr(mlx->text_oia2, &bpp, &line_b, &endian);
	pixels = (uint32_t *)img_data;
	scale = 4;
	i = 0;
	while (i < 64 / scale && (y + i) < 800)
	{
		j = 0;
		while (j < 64 / scale && (x + j) < 1000)
		{
			color = pixels[(i * scale) * 64 + (j * scale)];
			if ((color & 0xFF000000) == 0)
				my_mlx_pixel_put(data, x + j, y + i, color);
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
	icon_size = 16;
	p_x = (data->player_x * width) - (icon_size / 2);
	p_y = (data->player_y * height) - (icon_size / 2);
	if (p_x < 5)
		p_x = 5;
	if (p_y < 5)
		p_y = 5;
	if (p_x + icon_size > 185)
		p_x = 185 - icon_size;
	if (p_y + icon_size > 185)
		p_y = 185 - icon_size;
	draw_player(&data->mlx, data, p_x, p_y);
}
