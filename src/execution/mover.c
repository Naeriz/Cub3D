#include "../cub3d.h"

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
	mlx_destroy_image(data->mlx.mlx, data->mlx.image);
	data->mlx.image = mlx_new_image(data->mlx.mlx, 1000, 800);
	data->mlx.address = mlx_get_data_addr(data->mlx.image, &data->mlx.bpp,
			&data->mlx.line_b, &data->mlx.endian);
	init_rays(&data->mlx, data);
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

void	change_checker(int key, t_map *data)
{
	double	temp_x;
	double	temp_y;

	temp_x = data->player_x;
	temp_y = data->player_y;
	printf("%f\n", data->player_y);
	printf("%f\n\n", data->player_x);
	change_pos(key, data);
	data->player_x += temp_x;
	data->player_y += temp_y;
	printf("%f\n", data->player_y);
	printf("%f\n", data->player_x);
	if (data->player_y < 1 || data->player_y > data->height - 1 || data->player_x < 1 || data->player_x > ft_strlen(data->map[(int)data->player_y]) - 1.2)
	{
		printf("WAAA\n");
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