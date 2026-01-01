/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 20:18:15 by sionow            #+#    #+#             */
/*   Updated: 2026/01/01 20:28:40 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char	*dest;

	dest = data->mlx.address + (y * data->mlx.line_b + x * (data->mlx.bpp / 8)); //gives mem adress position of what pixel
	*(unsigned int *)dest = color; //* before unsig int makes only change to value
}

void	draw_column(t_map *data, int col, double distance, double side)
{
	double	height;

	height = 800 / distance;
	if (distance <= 0) //we r at wall
		height = 800;
	if (height < 1) //if wall too far away min height for wall
		height = 1;
	render_vertical(data, col, height, side);
}
