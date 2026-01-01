/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:04:46 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/01 19:48:03 by sionow           ###   ########.fr       */
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
#include <stdint.h>

# define W 119
# define A 97
# define S 115
# define D 100
# define ESCAPE 65307
# define L_FOV 65361
# define R_FOV 65363


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

typedef struct s_mlx
{
	void	*mlx;
	char	*address; //which image
	void	*window;
	void	*image;
	double	real_p_dir; //radian
	int		bpp; //amount of bits on screen
	int		endian; //0 or 1 how argb bytes organized
	int		line_b; //width * 4
	void	*text_north;
	void	*text_east;
	void	*text_south;
	void	*text_west;
	char	*north_adr;
	char	*east_adr;
	char	*south_adr;
	char	*west_adr;
	int		img_wdth;
	int		img_hght;
	int		angle_x;
	int		angle_y;
}	t_mlx;

typedef struct s_map
{
	char		**map;
	t_mlx		mlx;
	int			height;
	int			width;
	int			fd;
	int			line_count;
	char		*path;
	t_textures	*textures;
	double		player_x;
	double		player_y;
	char		player_dir; // N, E, S, W
	int			wall_s; //beginn wall
	int			wall_e; //end wall
	int			w;
	int			a;
	int			s;
	int			d;
	int			r_fov;
	int			l_fov;
	int			start;
}	t_map;



typedef struct s_ray //all shits needed for raycasting math brainfuck
{ //dda for speed
	t_mlx	mlx;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall_x; //how much wall hit w ray
	double	distance;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		view_side;
}	t_ray;

//basic.c

int		check_extension(char *path);
int		parse_args(t_map *map, char **av);
char	*skip_spaces(char *line);

//init.c

void	init_textures(t_textures *textures); //init textures and colors for floor ceiling
void	init_data(t_map *data);

//parse.c

int	check_textures_filled(t_map *data);
int		parse_line(char *line, t_map *data);
int		parse_data(t_map *data);

//parse_map.c

int		get_max_width(t_list *map_list);
void	get_player_pos(t_map *data);
int		list_to_array(t_map *data, t_list *map_list);
int		parse_map(t_map *data, char *first_line);

//utils.c

int		fill_texture_path(char **texture, char *line); //temp for now have to work this
int		fill_color(int *color, char *line); //same here
int		check_rgb_values(int *rgb);
void	remove_newline(char *str);
int		check_file_access(char *path);

//validate.c
int		check_map_validity(t_map *data);

//tabs_spaces.c
int		get_expanded_len(char *str);
char	*expand_tabs(char *line);

//free.c

void	free_tab(char **tab);
void	free_textures(t_textures *textures);
void	free_data(t_map *data);
int		exit_error(t_map *data, char *msg);

//exec
void	init_mlx(t_mlx *mlx, t_map *data);
void	init_rays(t_mlx *mlx, t_map *data);
int		key_detect(t_map *data);
int		key_press(int key, t_map *data);
int		key_release(int key, t_map *data);
int		close_window(t_map *data);
void	my_mlx_pixel_put(t_map *data, int x, int y, int color);

//mover
void	change_checker(int key, t_map *data);
void	foven(int key, t_map *data);

//textures
void	textures_init(t_mlx *mlx, t_map *data);
void	get_wall_dir(t_map *data, t_ray ray);
void	apply_text(t_map *data, int col, int y, double pos);
#endif