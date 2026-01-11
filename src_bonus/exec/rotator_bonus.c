/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotator_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:52:12 by sionow            #+#    #+#             */
/*   Updated: 2026/01/11 20:34:21 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	mouse_mover(int x, int y, t_map *data)
{
	static int	prev_x = 500;

	(void)y;
	if (x == prev_x)
		return (0);
	else if (x < prev_x)
		data->l_fov = 0;
	else if (x > prev_x)
		data->r_fov = 0;
	prev_x = x;
	return (0);
}
