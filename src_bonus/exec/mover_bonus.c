/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:58:22 by sionow            #+#    #+#             */
/*   Updated: 2026/01/07 22:58:55 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

double	convert_dir(char dir)
{
	double	ret;

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

int	key_detect(t_map *data)
{
	swap_img(data);
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
	if (data->start == 0)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.image);
		data->mlx.image = mlx_new_image(data->mlx.mlx, 1000, 800);
		data->mlx.address = mlx_get_data_addr(data->mlx.image, &data->mlx.bpp,
				&data->mlx.line_b, &data->mlx.endian);
		init_rays(&data->mlx, data);
		data->start++;
	}
	return (0);
}

void	foven(int key, t_map *data)
{
	if (key == R_FOV)
		data->mlx.real_p_dir += 0.030; //works well
	else if (key == L_FOV)
		data->mlx.real_p_dir -= 0.030;
	if (data->mlx.real_p_dir < 0)
		data->mlx.real_p_dir += 2 * M_PI;
	if (data->mlx.real_p_dir > 2 * M_PI) //if above 360deg make back to 0
		data->mlx.real_p_dir -= 2 * M_PI;
	if (data->mlx.image)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.image);
		data->mlx.image = mlx_new_image(data->mlx.mlx, 1000, 800);
		data->mlx.address = mlx_get_data_addr(data->mlx.image, &data->mlx.bpp,
				&data->mlx.line_b, &data->mlx.endian);
		init_rays(&data->mlx, data);
	}
	data->l_fov = 1;
	data->r_fov = 1;
}

void	change_pos(int key, t_map *data)
{
	double	dir_x;
	double	dir_y;

	dir_x = cos(data->mlx.real_p_dir);
	dir_y = sin(data->mlx.real_p_dir);
	if (key == W)
	{
		data->player_x = 0.1 * dir_x;
		data->player_y = 0.1 * dir_y;
	}
	else if (key == D)
	{
		data->player_x = 0.1 * -dir_y;
		data->player_y = 0.1 * dir_x;
	}
	else if (key == S)
	{
		data->player_x = -0.1 * dir_x;
		data->player_y = -0.1 * dir_y;
	}
	else if (key == A)
	{
		data->player_x = 0.1 * dir_y;
		data->player_y = -0.1 * dir_x;
	}
}

int		edger(t_map *d, int cur_x, int cur_y)
{
	int	x;
	int	y;

	x = d->player_x;
	y = d->player_y;
	if (d->map[cur_y + 1][cur_x] == '1' && d->map[cur_y][cur_x - 1] == '1')
		if (d->map[y - 1][x] == '1' && d->map[y][x + 1] == '1')
			return (1);
	if (d->map[cur_y + 1][cur_x] == '1' && d->map[cur_y][cur_x + 1] == '1')
		if (d->map[y - 1][x] == '1' && d->map[y][x - 1] == '1')
			return (1);
	if (d->map[cur_y - 1][cur_x] == '1' && d->map[cur_y][cur_x - 1] == '1')
		if (d->map[y + 1][x] == '1' && d->map[y][x + 1] == '1')
			return (1);
	if (d->map[cur_y - 1][cur_x] == '1' && d->map[cur_y][cur_x + 1] == '1')
		if (d->map[y + 1][x] == '1' && d->map[y][x - 1] == '1')
			return (1);
	return (0);
}

void	change_checker(int key, t_map *data)
{
	double	temp_x;
	double	temp_y;

	temp_x = data->player_x;
	temp_y = data->player_y;
	change_pos(key, data);
	data->player_x += temp_x;
	data->player_y += temp_y;
	if (data->player_y < 1 || data->player_y > data->height - 1
		|| data->player_x < 1
		|| data->player_x > ft_strlen(data->map[(int)data->player_y]) - 1.01 
		|| data->map[(int)data->player_y][(int)data->player_x] == '1'
		|| edger(data, (int)temp_x, (int)temp_y) == 1)
	{
		data->player_x = temp_x;
		data->player_y = temp_y;
		return ;
	}
	mlx_destroy_image(data->mlx.mlx, data->mlx.image);
	data->mlx.image = mlx_new_image(data->mlx.mlx, 1000, 800);
	data->mlx.address = mlx_get_data_addr(data->mlx.image, &data->mlx.bpp,
			&data->mlx.line_b, &data->mlx.endian);
	init_rays(&data->mlx, data);
}
