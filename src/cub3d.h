/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:04:46 by amezoe            #+#    #+#             */
/*   Updated: 2025/11/26 19:33:43 by sionow           ###   ########.fr       */
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
	char		player_dir; // N, E, S, W
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
	int		bpp; //amount of bits on screen
	int		endian; //0 or 1 how argb bytes organized
	int		line_b; //width * 4
	void	*text_north;
	void	*text_east;
	void	*text_south;
	void	*text_west;
}	t_mlx;


typedef struct s_ray //all shits needed for raycasting math brainfuck
{
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall_x;
	double	distance;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		view_side;
}	t_ray

//basic.c

int	check_extension(char *path);
int	parse_args(t_map *map, char **av);
char	*skip_spaces(char *line);

//init.c

void	init_textures(t_textures *textures); //init textures and colors for floor ceiling
void	init_data(t_map *data);

//parse.c

int	parse_line(char *line, t_map *data);
int	parse_data(t_map *data);

//utils.c

int	fill_texture_path(char **texture, char *line); //temp for now have to work this
int	fill_color(int *color, char *line); //same here
int	check_rgb_values(int *rgb);
void	remove_newline(char *str);








#endif