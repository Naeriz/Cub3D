/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normi_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 20:15:33 by sionow            #+#    #+#             */
/*   Updated: 2026/01/01 20:26:34 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_map *data)
{
	(void) data;
	exit(0);
}

int	key_press(int key, t_map *data)
{
	if (key == ESCAPE)
		close_window(data);
	if (key == W)
		data->w = 0;
	else if (key == A)
		data->a = 0;
	else if (key == S)
		data->s = 0;
	else if (key == D)
		data->d = 0;
	else if (key == R_FOV)
		data->r_fov = 0;
	else if (key == L_FOV)
		data->l_fov = 0;
	return (0);
}

int	key_release(int key, t_map *data)
{
	if (key == W)
		data->w = 1;
	else if (key == A)
		data->a = 1;
	else if (key == S)
		data->s = 1;
	else if (key == D)
		data->d = 1;
	else if (key == R_FOV)
		data->r_fov = 1;
	else if (key == L_FOV)
		data->l_fov = 1;
	return (0);
}
