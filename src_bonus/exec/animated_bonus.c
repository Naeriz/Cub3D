/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:45:05 by sionow            #+#    #+#             */
/*   Updated: 2026/01/07 22:59:07 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	close_window2(t_map *data)
{
	free_all2(&data->mlx, data);
	exit(0);
}

void	free_all2(t_mlx *mlx, t_map *data)
{
	if (mlx->text_north)
		mlx_destroy_image(mlx->mlx, mlx->text_north);
	if (mlx->text_north2)
		mlx_destroy_image(mlx->mlx, mlx->text_north2);
	if (mlx->text_east)
		mlx_destroy_image(mlx->mlx, mlx->text_east);
	if (mlx->text_south)
		mlx_destroy_image(mlx->mlx, mlx->text_south);
	if (mlx->text_west)
		mlx_destroy_image(mlx->mlx, mlx->text_west);
	if (mlx->image)
		mlx_destroy_image(mlx->mlx, mlx->image);
	if (mlx->window)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(data->textures->north);
	free(data->textures->east);
	free(data->textures->south);
	free(data->textures->west);
	free(data->textures);
	if (data->map)
		free_map(data->map);
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

void	init_img(t_mlx *mlx, t_map *data)
{
	if (!mlx->text_north || !mlx->north_adr)
	{
		printf("Error:\n xpm conversion failed\n");
		free_all2(mlx, data);
		exit(1);
	}
}
