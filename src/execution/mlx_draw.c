/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 20:18:15 by sionow            #+#    #+#             */
/*   Updated: 2026/02/08 02:55:52 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	normi(t_map *data)
{
	if (fmod(data->player_y, 1.0) < 0.001)
		data->player_y += 0.01;
	if (fmod(data->player_x, 1.0) < 0.001)
		data->player_x += 0.01;
}

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char	*dest;

	dest = data->mlx.address + (y * data->mlx.line_b + x * (data->mlx.bpp / 8));
	*(unsigned int *)dest = color;
}

void	draw_column(t_map *data, int col, double distance, double side)
{
	double	height;

	height = 800 / distance;
	if (distance <= 0)
		height = 800;
	if (height < 1)
		height = 1;
	render_vertical(data, col, height, side);
}
