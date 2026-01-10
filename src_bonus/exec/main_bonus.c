/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:37:24 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/10 23:22:39 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	start_game(t_mlx *mlx, t_map *data)
{
	mlx_hook(mlx->window, 2, 1L << 0, key_press, data);
	mlx_hook(mlx->window, 3, 1L << 1, key_release, data);
	mlx_hook(mlx->window, 17, 1L << 17, close_window2, data);
	mlx_hook(mlx->window, 6, 1L << 6, mouse_mover, data);
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
	init_mlx(&mlx, &data);
	init_rays(&mlx, &data);
	start_game(&mlx, &data);
	free_data(&data);
	return (0);
}
