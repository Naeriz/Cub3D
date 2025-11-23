/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 07:47:14 by amezoe            #+#    #+#             */
/*   Updated: 2025/11/23 08:04:49 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_line(char *line, t_map *data)
{
	char	*content;

	content = skip_spaces(line);
	if (!*content || *content == '\n')
		return (0);
	if (ft_strncmp(content, "NO", 2) == 0 && content[2] == ' ')
		return (fill_texture_path(&data->textures->north, content));
	if (ft_strncmp(content, "SO", 2) == 0 && content[2] == ' ')
		return (fill_texture_path(&data->textures->south, content));
	if (ft_strncmp(content, "WE", 2) == 0 && content[2] == ' ')
		return (fill_texture_path(&data->textures->west, content));
	if (ft_strncmp(content, "EA", 2) == 0 && content[2] == ' ')
		return (fill_texture_path(&data->textures->east, content));
	if (ft_strncmp(content, "F", 1) == 0 && content[1] == ' ')
		return (fill_color(&data->textures->floor, content));
	if (ft_strncmp(content, "C", 1) == 0 && content[1] == ' ')
		return (fill_color(&data->textures->ceiling, content));
	//check if map starts, have to check if textures are all set before this
	if (*content == '1' || *content == '0')
		return (2);
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
			return (printf("error\n invalid line found in .cub\n"), 1);
		}
		if (status == 2)
		{
			//we have the map so we stop and the parsing will deal with this.
			free(line); //remove this when i have the implementation for parse_map, we will free it there, this is temporary
			break ; 
		}
		free(line);
	}
	return (0);
}