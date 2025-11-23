/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:36:07 by amezoe            #+#    #+#             */
/*   Updated: 2025/11/23 08:04:45 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor =-1;
	textures->ceiling = -1; // i messed up, we need -1 cuz 0 is rgb black
}

void	init_data(t_map *data)
{
	data->map = NULL;
	data->height = 0;
	data->width = 0;
	data->fd = 0;
	data->line_count = 0;
	data->path = NULL;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
	{
		perror("malloc failed");
		exit(1);
	}
	init_textures(data->textures);
}
