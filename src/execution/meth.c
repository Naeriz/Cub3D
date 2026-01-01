/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:26:13 by sionow            #+#    #+#             */
/*   Updated: 2026/01/01 20:34:42 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// mlx_new_window()
// mlx_destroy_display(mlx->mlx)

void	visible_height(t_map *data, double *step, double *pos, double height)
{
	int	draw_s;
	int	draw_e;

	data->wall_s = (800 - height) / 2;
	data->wall_e = (data->wall_s + height);
	draw_s = fmax(data->wall_s, 0); //to not draw above or below
	draw_e = fmin(data->wall_e, 800);
	if (draw_e <= draw_s)
	{
		data->wall_s = 0;
		data->wall_e = 0;
		return ;
	}
	*step = data->mlx.img_hght / height;
	*pos = (draw_s - data->wall_s) * (*step);
	*pos = fmax(*pos, 0);
	*pos = fmin(*pos, 96 - 1);
	data->wall_s = draw_s;
	data->wall_e = draw_e;
}

void	render_vertical(t_map *data, int col, double height, double side)
{
	double	step;
	double	pos;
	int		y;

	visible_height(data, &step, &pos, height);
	data->mlx.angle_x = (int)(side * data->mlx.img_wdth);
	y = 0;
	while (y < 800)
	{
		if (y < data->wall_s)
			my_mlx_pixel_put(data, col, y, data->textures->ceiling);
		else if (y < data->wall_e)
		{
			apply_text(data, col, y, pos);
			pos += step;
			pos = fmin(pos, data->mlx.img_hght - 1);
		}
		else
			my_mlx_pixel_put(data, col, y, data->textures->floor);
		y++;
	}
}

//make ray go forward 1 grid a time
void	dda_step(t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x = ray->side_x + ray->delta_x;
		ray->map_x = ray->map_x + ray->step_x;
		ray->view_side = 0;
	}
	else
	{
		ray->side_y = ray->side_y + ray->delta_y;
		ray->map_y = ray->map_y + ray->step_y;
		ray->view_side = 1;
	}
}

double	final_distance(t_ray *ray, t_map *data, double ray_angle, double *side)
{
	int	wall; //norminette rayviewside too long

	wall = ray->view_side;
	if (ray->view_side == 0)
	{
		ray->distance = (ray->map_x - data->player_x
				+ (1 - ray->step_x) / 2) / ray->dir_x; //to see if ray approach from left or right
		ray->wall_x = data->player_y + ray->dir_y * ray->distance; //textures
	}
	else
	{
		ray->distance = (ray->map_y - data->player_y
				+ (1 - ray->step_y) / 2) / ray->dir_y; //above or under
		ray->wall_x = data->player_x + ray->dir_x * ray->distance;
	}
	ray->wall_x = ray->wall_x - floor(ray->wall_x); //floor retardus makes for example 20.97 into 0.97, for tetxures bcs work w 0 to 1
	if ((wall == 0 && ray->step_x == -1) || (wall == 1 && ray->step_y == -1)) //if u look north w cube infront, u look at south part of cube
		ray->wall_x = 1 - ray->wall_x;
	*side = ray->wall_x;
	return (ray->distance * cos(ray_angle - ray->mlx.real_p_dir)); //fisheye bcs not same length rays, cos make sides shorter = normal vision
}

//each ray one by one
//checks if out of map or found wall
double	ray_checker(t_mlx *mlx, t_map *data, double ray_angle, double *side)
{
	t_ray	ray;

	init_struct_ray(mlx, &ray, data, ray_angle);
	while (1)
	{
		dda_step(&ray);
		if (ray.map_y >= data->height
			|| ray.map_x >= (int)ft_strlen(data->map[ray.map_y]))
			return (-1);
		if (data->map[ray.map_y][ray.map_x] == '1')
			break ;
	}
	get_wall_dir(data, ray); //to get right texture
	return (final_distance(&ray, data, ray_angle, side));
}
