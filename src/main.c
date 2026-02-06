/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:37:24 by amezoe            #+#    #+#             */
/*   Updated: 2026/02/06 15:55:09 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_mlx *mlx, t_map *data)
{
	mlx_hook(mlx->window, 2, 1L << 0, key_press, data);
	mlx_hook(mlx->window, 3, 1L << 1, key_release, data);
	mlx_hook(mlx->window, 17, 1L << 17, close_window, data);
	mlx_loop_hook(mlx->mlx, key_detect, data);
	mlx_loop(mlx->mlx);
}

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
	if (parse_args(&data, av) != 0 || parse_data(&data) != 0)
	{
		free_data(&data);
		return (1);
	}
	printf("MAP IS:\n");
	for (size_t i = 0; data.map[i]; i++) {
		for (size_t j = 0; j < ft_strlen(data.map[i]); j++) {
			if (data.map[i][j] == ' ') {
				printf("M");
			} else {
				printf("%c", data.map[i][j]);
			}
		}
		printf("\n");
	}
	init_mlx(&mlx, &data);
	init_rays(&mlx, &data);
	start_game(&mlx, &data);
	free_data(&data);
	return (0);
}
