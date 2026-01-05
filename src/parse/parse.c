/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 07:47:14 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/04 19:35:37 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_textures_filled(t_map *data)
{
	if (!data->textures->north || !data->textures->south
		|| !data->textures->west || !data->textures->east)
		return (0);
	if (data->textures->floor == -1 || data->textures->ceiling == -1)
		return (0);
	return (1);
}

int is_empty(char c)
{
	return (c == ' ' || c == '\t');
}

int	parse_line(char *line, t_map *data)
{
	char	*content;

	content = skip_spaces(line);
	if (!*content || *content == '\n')
		return (0);
	if (ft_strncmp(content, "NO", 2) == 0 && is_empty(content[2]))
		return (fill_texture_path(&data->textures->north, content));
	if (ft_strncmp(content, "SO", 2) == 0 && is_empty(content[2]))
		return (fill_texture_path(&data->textures->south, content));
	if (ft_strncmp(content, "WE", 2) == 0 && is_empty(content[2]))
		return (fill_texture_path(&data->textures->west, content));
	if (ft_strncmp(content, "EA", 2) == 0 && is_empty(content[2]))
		return (fill_texture_path(&data->textures->east, content));
	if (ft_strncmp(content, "F", 1) == 0 && is_empty(content[1]))
		return (fill_color(&data->textures->floor, content));
	if (ft_strncmp(content, "C", 1) == 0 && is_empty(content[1]))
		return (fill_color(&data->textures->ceiling, content));
	//check if map starts, have to check if textures are all set before this
	if (*content == '1' || *content == '0')
	{
		if (!check_textures_filled(data))
		{
			printf("Error\nMap started before all textures were fedined\n");
			return (1);
		}
		return (2);
	}
	return (1);
}

int	parse_data(t_map *data)
{
	char	*line;
	int		status;

	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		status = parse_line(line, data);
		if (status == 1)
		{
			free(line);
			//i remove this so we dont get the double errors
			//return (printf("error\n invalid line found in .cub\n"), 1);
			return (1);
		}
		if (status == 2)
		{
			if(parse_map(data, line))
				return (1);
			return (0);
		}
		free(line);
	}
	printf("Error\nfile is empty or missing map");
	return (1);
}
