/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:26:13 by sionow            #+#    #+#             */
/*   Updated: 2025/12/01 19:02:49 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_new_window()
mlx_destroy_display(mlx->mlx)
init_textures

//dont ask I dont fucking know anymore big meth
//dda prep
void	init_struct_ray(t_ray *ray, t_map *data, double ray_angle)
{
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)data->player_x;
	ray->map_y = (int)data->player_y;
	ray->delta_x = fabs(1 / ray->dir_x + 0.0000001); //float absolute (same as abs)
	ray->delta_y = fabs(1 / ray->dir_y + 0.0000001); //securit so its not fully 0
	ray->step_x = 1;
	if (ray->dir_x > 0)
		ray->side_x = (ray->map_x + 1.0 - data->player_x) * ray->delta_x;
	else
	{
		ray->step_x = -1;
		ray->side_x = (data->player_x - ray->map_x) * ray->delta_x;
	}
	ray->step_y = 1;
	if (ray->dir_y > 0)
		ray->side_y = (ray->map_y + 1.0 - data->player_y) * ray->delta_y;
	else
	{
		ray->step_y = -1;
		ray->side_y = (data->player_y - ray->map_y) * ray->delta_y;
	}
}

void	draw_column(t_map *data, int col, double distance, double side)
{
	
}

double	ray_checker(t_mlx *mlx, t_maps *data, double ray_angle, double *side)
{
	t_ray ray;
	
	init_struct_ray(&ray, data, ray_angle);
}

double	convert_dir(char dir)
{
	double ret;

	if (dir == 'N')
		ret = 3 * M_PI / 2;
	if (dir == 'E')
		ret = 0;
	if (dir == 'S')
		ret = (M_PI / 2);
	if (dir == 'W')
		ret = M_PI;
	return (ret)
}

void	init_rays(t_mlx *mlx, t_maps *data)
{
	double	fov;
	double	distance;
	double	side;
	double 	ray_angle;
	int		col; //which column we at. left to right
	
	fov = 72 * (M_PI / 180);
	ray_angle = mlx->real_p_dir - (fov / 2); //radian meth
	col = 0;
	
	while (col < 1000)
	{
		distance = ray_checker(mlx, data, ray_angle, &side); //side mod in func
		if (distance != -1)
			draw_column(data, col, distance, side);
		ray_angle += fov / data->width;
		col++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image, 0 , 0);
}

void	init_mlx(t_mlx *mlx, t_map *data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		write(2, "Error\n", 6);
		write(2, "mlx ain't init :c\n", 18);
		exit(1);
	}
	mlx->window = mlx_new_window(mlx->mlx, 1000, 800, "cub3d");
	if (!mlx->window)
	{
		write(2, "Error\n", 6);
		write(2, "window ain't windowing :c\n", 26);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		exit(1);
	}
	//init_textures(mlx, data);
	mlx->real_p_dir = convert_dir(data->player_dir);
	graphic_init(mlx);
}

void	graphic_init(t_mlx *mlx)
{
	mlx->image = mlx_new_image(mlx->mlx, 1000, 800);
	if (!mlx->image)
	{
		write(2, "Error\n", 6);
		write(2, "image ain't imaging :c\n", 23);
		mlx_destroy_window(mlx->mlx, mlx->window);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		exit(1);
	}
	mlx->address = mlx_get_data_addr(mlx->image, &mlx->bpp, 
		&mlx->endian, &mlx->line_b);
	if (!mlx->address)
	{
		write(2, "Error\n", 6);
		write(2, "image ain't imaging :c\n", 23);
		mlx_destroy_image(mlx->mlx, mlx->image);
		mlx_destroy_window(mlx->mlx, mlx->window);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		exit(1);
	}
}
