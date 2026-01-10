/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:58:03 by sionow            #+#    #+#             */
/*   Updated: 2026/01/10 23:14:35 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	apply_text(t_map *data, int col, int y, double pos)
{
	uint32_t	*tex;
	int			offset;

	data->mlx.angle_y = (int)pos % data->mlx.img_hght;
	if (data->mlx.angle_x < 0)
		data->mlx.angle_x = 0;
	else if (data->mlx.angle_x >= data->mlx.img_wdth)
		data->mlx.angle_x = data->mlx.img_wdth - 1;
	if (data->mlx.angle_y < 0)
		data->mlx.angle_y = 0;
	else if (data->mlx.angle_y >= data->mlx.img_hght)
		data->mlx.angle_y = data->mlx.img_hght - 1;
	if (data->player_dir == 'N')
		tex = (uint32_t *)data->mlx.north_adr;
	else if (data->player_dir == 'S')
		tex = (uint32_t *)data->mlx.south_adr;
	else if (data->player_dir == 'W')
		tex = (uint32_t *)data->mlx.west_adr;
	else if (data->player_dir == 'E')
		tex = (uint32_t *)data->mlx.east_adr;
	offset = (data->mlx.angle_y * data->mlx.img_wdth + data->mlx.angle_x);
	if (offset >= 0 && offset < data->mlx.img_hght * data->mlx.img_wdth)
		my_mlx_pixel_put(data, col, y, tex[offset]);
}

void	get_wall_dir(t_map *data, t_ray ray)
{
	if (ray.view_side == 0)
	{
		if (ray.step_x > 0)
			data->player_dir = 'E';
		else
			data->player_dir = 'W';
	}
	else
	{
		if (ray.step_y > 0)
			data->player_dir = 'S';
		else
			data->player_dir = 'N';
	}
}

void	getadr(t_mlx *mlx, t_map *data)
{
	mlx->north_adr = mlx_get_data_addr(mlx->text_north, &mlx->bpp,
			&mlx->line_b, &mlx->endian);
	mlx->east_adr = mlx_get_data_addr(mlx->text_east, &mlx->bpp,
			&mlx->line_b, &mlx->endian);
	mlx->south_adr = mlx_get_data_addr(mlx->text_south, &mlx->bpp,
			&mlx->line_b, &mlx->endian);
	mlx->west_adr = mlx_get_data_addr(mlx->text_west, &mlx->bpp,
			&mlx->line_b, &mlx->endian);
	if (!mlx->north_adr || !mlx->east_adr || !mlx->south_adr
		|| !mlx->west_adr)
	{
		free_all(mlx, data);
		exit(1);
	}
}

void	textures_init(t_mlx *mlx, t_map *data)
{
	mlx->text_north = mlx_xpm_file_to_image(mlx->mlx, data->textures->north,
			&mlx->img_wdth, &mlx->img_hght);
	mlx->text_east = mlx_xpm_file_to_image(mlx->mlx, data->textures->east,
			&mlx->img_wdth, &mlx->img_hght);
	mlx->text_south = mlx_xpm_file_to_image(mlx->mlx, data->textures->south,
			&mlx->img_wdth, &mlx->img_hght);
	mlx->text_west = mlx_xpm_file_to_image(mlx->mlx, data->textures->west,
			&mlx->img_wdth, &mlx->img_hght);
	if (!mlx->text_north || !mlx->text_east || !mlx->text_south
		|| !mlx->text_west)
	{
		printf("Error:\n xpm conversion failed\n");
		free_all(mlx, data);
		exit(1);
	}
	getadr(mlx, data);
}
