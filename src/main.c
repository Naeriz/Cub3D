/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:37:24 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/07 17:59:50 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (1);
	if (parse_data(&data) != 0)
		return (1);
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
	mlx_loop(mlx.mlx);
	return (0);
}
