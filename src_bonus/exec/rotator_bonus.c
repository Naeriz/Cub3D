/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotator_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:52:12 by sionow            #+#    #+#             */
/*   Updated: 2026/01/04 20:20:08 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	limiter(t_map *data, int *x, int y, int *prev_x)
{
	if (*x > 980) //to bring mouse back on other side of window
	{
		*x = 20;
		*prev_x = *x;
		mlx_mouse_move(data->mlx.mlx, data->mlx.window, *x, y);
	}
	if (*x < 20)
	{
		*x = 980;
		*prev_x = *x;
		mlx_mouse_move(data->mlx.mlx, data->mlx.window, *x, y);
	}
}

int	mouse_mover(int x, int y, t_map *data)
{
	static int prev_x = 500;
	// int movement;

	// movement = x - prev_x;
	// if (movement < 0)
	// 	movement = -movement;		
	// if (movement < 1)
	// 	return (0);
	limiter(data, &x, y, &prev_x);
	if (x == prev_x)
		return (0);
	else if (x < prev_x)
		data->l_fov = 0;
	else if (x > prev_x)
		data->r_fov = 0;
	prev_x = x;
	return (0);
}