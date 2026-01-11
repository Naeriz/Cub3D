/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oia_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:22:16 by sionow            #+#    #+#             */
/*   Updated: 2026/01/11 19:40:48 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

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