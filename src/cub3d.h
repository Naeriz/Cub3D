/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:04:46 by amezoe            #+#    #+#             */
/*   Updated: 2025/11/19 09:34:37 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../inc/minilibx-linux/mlx.h"
#include "../inc/get_next_line/get_next_line.h"
#include "../inc/libft/libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//parse structs

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor;// hex color code
	int				ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}	t_textures;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	int			fd;
	int			line_count;
	char		*path;
	t_textures	*textures;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_map;

#endif