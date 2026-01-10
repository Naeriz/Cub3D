/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normi_dump_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 20:15:33 by sionow            #+#    #+#             */
/*   Updated: 2026/01/10 22:27:15 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	mlx_free(t_mlx *mlx)
{
	if (mlx->text_door1)
		mlx_destroy_image(mlx->mlx, mlx->text_door1);
	if (mlx->text_door2)
		mlx_destroy_image(mlx->mlx, mlx->text_door2);
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
}

void	free_all2(t_mlx *mlx, t_map *data)
{
	mlx_free(mlx);
	free(data->textures->north);
	free(data->textures->east);
	free(data->textures->south);
	free(data->textures->west);
	free(data->textures);
	if (data->map)
		free_map(data->map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	key_press(int key, t_map *data)
{
	if (key == ESCAPE)
		close_window2(data);
	if (key == SPACE)
		door_dist(data);
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
