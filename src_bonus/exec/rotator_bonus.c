/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotator_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:52:12 by sionow            #+#    #+#             */
/*   Updated: 2026/01/04 18:02:24 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	limiter(t_map *data, int x, int y)
{
	if (x > 980) //to bring mouse back on other side of window
	{
		x = 20;
		mlx_mouse_move(data->mlx.mlx, data->mlx.window, x, y);
	}
	if (x < 20)
	{
		x = 980;
		mlx_mouse_move(data->mlx.mlx, data->mlx.window, x, y);
	}
}

int	mouse_mover(int x, int y, t_map *data)
{
	static int prev_x = 500;
	limiter(data, x, y);
	if (x == prev_x)
		return (0);
	else if (x < prev_x)
		foven(L_FOV, data);
	else if (x > prev_x)
		foven(R_FOV, data);
	prev_x = x;
	return (0);
}