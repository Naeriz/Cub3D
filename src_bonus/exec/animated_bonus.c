/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:45:05 by sionow            #+#    #+#             */
/*   Updated: 2026/01/11 19:30:46 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	close_window2(t_map *data)
{
	free_all2(&data->mlx, data);
	exit(0);
}

void	swap_img(t_map *data)
{
	clock_t	now;
	clock_t	between;

	now = clock();
	between = (now - data->last_frame) * 1000 / CLOCKS_PER_SEC;
	if (between >= 400)
	{
		data->last_frame = now;
		if (data->north == 2)
			data->north = 1;
		else
			data->north = 2;
		mlx_destroy_image(data->mlx.mlx, data->mlx.image);
		data->mlx.image = mlx_new_image(data->mlx.mlx, 1000, 800);
		data->mlx.address = mlx_get_data_addr(data->mlx.image, &data->mlx.bpp,
				&data->mlx.line_b, &data->mlx.endian);
		init_rays(&data->mlx, data);
	}
}
