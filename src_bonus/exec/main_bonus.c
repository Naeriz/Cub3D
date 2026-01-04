/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:37:24 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/04 18:12:53 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	main(int ac, char **av)
{
	t_map	data;
	t_mlx	mlx;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nuse ./cub3D [path/to/map.cub]\n", 2);
		return (1);
	}

	init_data(&data);
	if (parse_args(&data, av) != 0)
	{
		free_data(&data);
		return (1);
	}
	
	if (parse_data(&data) != 0)
	{
		free_data(&data);
		return (1);
	}
	printf("works, map is loaded\n");
	close(data.fd);
	printf("	---MAP INFO---	\n");
	printf("	height = %d\n", data.height);
	printf("	width = %d\n", data.width);
	printf("	player_x = %f\n", data.player_x);
	printf("	player_y = %f\n", data.player_y);
	printf("	Direction = %c\n", data.player_dir);
	printf("	Ceiling color = %d\n", data.textures->ceiling);
	printf("	Floor color = %d\n\n", data.textures->floor);
	init_mlx(&mlx, &data);
	init_rays(&mlx, &data);
	mlx_hook(mlx.window, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.window, 3, 1L << 1, key_release, &data);
	mlx_hook(mlx.window, 17, 1L << 17, close_window, &data);
	mlx_hook(mlx.window, 6, 1L << 6, mouse_mover, &data);
	mlx_loop_hook(mlx.mlx, key_detect, &data);
	mlx_loop(mlx.mlx);

	free_data(&data);
	return (0);
}
