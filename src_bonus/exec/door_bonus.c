/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:23:10 by sionow            #+#    #+#             */
/*   Updated: 2026/01/10 22:28:03 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	door(t_map *data)
{
	if (data->map[(int)data->player_y][(int)data->player_x] == 'D')
		data->map[(int)data->player_y][(int)data->player_x] = 'O';
	else if (data->map[(int)data->player_y][(int)data->player_x] == 'O')
		data->map[(int)data->player_y][(int)data->player_x] = 'D';
}

void	door_dist(t_map *data)
{
	double	dir_x;
	double	dir_y;
	double	temp_x;
	double	temp_y;

	temp_x = data->player_x;
	temp_y = data->player_y;
	dir_x = cos(data->mlx.real_p_dir);
	dir_y = sin(data->mlx.real_p_dir);
	data->player_x = 1 * dir_x;
	data->player_y = 1 * dir_y;
	data->player_x += temp_x;
	data->player_y += temp_y;
	if (data->map[(int)data->player_y][(int)data->player_x] == 'D')
		door(data);
	else if (data->map[(int)data->player_y][(int)data->player_x] == 'O')
		door(data);
	data->player_x = temp_x;
	data->player_y = temp_y;
}
