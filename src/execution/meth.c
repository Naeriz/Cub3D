/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:26:13 by sionow            #+#    #+#             */
/*   Updated: 2025/12/29 17:56:34 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// mlx_new_window()
// mlx_destroy_display(mlx->mlx)

int close_window(t_map *data)
{
	(void) data;
	exit(0);
}

int	key_detect(t_map *data)
{
	if (data->w == 0)
		change_checker(W, data);
	else if (data->s == 0)
		change_checker(S, data);
	else if (data->d == 0)
		change_checker(D, data);
	else if (data->a == 0)
		change_checker(A, data);
	if (data->r_fov == 0)
		foven(R_FOV, data);
	else if (data->l_fov == 0)
		foven(L_FOV, data);
	return (0);
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
int key_release(int key, t_map *data)
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

//dont ask I dont fucking know anymore big meth
//dda prep
void	init_struct_ray(t_mlx *mlx, t_ray *ray, t_map *data, double ray_angle)
{
	ray->mlx = *mlx;
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

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char *dest;
	
	dest = data->mlx.address + (y * data->mlx.line_b + x * (data->mlx.bpp / 8)); //gives mem adress position of what pixel
	*(unsigned int *)dest = color; //* before unsig int makes only change to value
}

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
	*step = 96 / height;
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

void	draw_column(t_map *data, int col, double distance, double side)
{
	double	height;
	
	height = 800 / distance;
	if (distance <= 0) //we r at wall
		height = 800;
	if (height < 1)//if wall too far away min height for wall
		height = 1;
	render_vertical(data, col, height, side);
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
	if ((wall == 0 && ray->step_x == -1) || (wall == 1 && ray->step_y == -1))//if u look north w cube infront, u look at south part of cube
		ray->wall_x = 1 - ray->wall_x;
	*side = ray->wall_x;
	return (ray->distance * cos(ray_angle - ray->mlx.real_p_dir)); //fisheye bcs not same length rays, cos make sides shorter = normal vision
}

//each ray one by one
//checks if out of map or found wall
double	ray_checker(t_mlx *mlx, t_map *data, double ray_angle, double *side)
{
	t_ray ray;

	init_struct_ray(mlx, &ray, data, ray_angle);
	while (1)
	{
		dda_step(&ray);
		if (ray.map_y >= data->height || ray.map_x >= (int)ft_strlen(data->map[ray.map_y]))
			return (-1);
		if (data->map[ray.map_y][ray.map_x] == '1')
			break ;	
	}
	get_wall_dir(data, ray); //to get right texture
	return (final_distance(&ray, data, ray_angle, side));
}

double	convert_dir(char dir)
{
	double ret;

	if (dir == 'N')
		ret = 3 * M_PI / 2;
	else if (dir == 'E')
		ret = 0;
	else if (dir == 'S')
		ret = (M_PI / 2);
	else if (dir == 'W')
		ret = M_PI;
	return (ret);
}

//double alot more precise than float(more nr behind ,)
void	init_rays(t_mlx *mlx, t_map *data)
{
	double	fov;
	double	distance;
	double	side;
	double	ray_angle;
	int		col; //which column we at. left to right
	
	fov = 72 * (M_PI / 180);
	ray_angle = mlx->real_p_dir - (fov / 2); //make start at left edge w radian meth
	col = 0;
	data->mlx = *mlx;
	while (col < 1000) //throws rays
	{
		distance = ray_checker(mlx, data, ray_angle, &side); //side mod in func
		if (distance != -1)
			draw_column(data, col, distance, side);
		ray_angle += fov / 1000;
		col++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image, 0, 0);
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
			&mlx->line_b, &mlx->endian);
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

void	init_mlx(t_mlx *mlx, t_map *data)
{
	mlx->mlx = mlx_init();
	mlx->north_adr = NULL;
	mlx->east_adr = NULL;
	mlx->south_adr = NULL;
	mlx->west_adr = NULL;
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
	textures_init(mlx, data);
}

