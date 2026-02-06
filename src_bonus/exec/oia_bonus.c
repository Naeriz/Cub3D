/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oia_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:22:16 by sionow            #+#    #+#             */
/*   Updated: 2026/02/06 20:31:28 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	nullsetter(t_mlx *mlx)
{
	mlx->north_adr = NULL;
	mlx->north_adr2 = NULL;
	mlx->east_adr = NULL;
	mlx->south_adr = NULL;
	mlx->west_adr = NULL;
	mlx->text_oia1 = NULL;
	mlx->text_oia2 = NULL;
	mlx->text_north = NULL;
	mlx->text_north2 = NULL;
	mlx->text_east = NULL;
	mlx->text_south = NULL;
	mlx->text_west = NULL;
	mlx->text_door1 = NULL;
	mlx->text_door2 = NULL;
}

void	init_oia(t_mlx *mlx)
{
	mlx->oia1_adr = NULL;
	mlx->oia2_adr = NULL;
}

void	oia_maker(t_mlx *mlx, t_map *data)
{
	mlx->text_oia1 = mlx_xpm_file_to_image(mlx->mlx, "inc/oia1.xpm",
			&mlx->img_wdth, &mlx->img_hght);
	mlx->text_oia2 = mlx_xpm_file_to_image(mlx->mlx, "inc/oia2.xpm",
			&mlx->img_wdth, &mlx->img_hght);
	if (!mlx->text_oia1 || !mlx->text_oia2)
	{
		printf("Error:\n xpm conversion failed\n");
		free_all2(mlx, data);
		exit(1);
	}
}
