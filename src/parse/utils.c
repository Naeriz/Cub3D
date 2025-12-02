/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 07:44:50 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/02 14:42:06 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	remove_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

int	check_rgb_values(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Error\ncolor value out of range 0-255\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_file_access(char *path)
{
	int		fd;
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error\nTexture must be an xpm file: %s\n", path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nTexture file cant be found: %s\n", path);
		return (1);
	}
	close(fd);
	return (0);
}

int	fill_texture_path(char **texture, char *line)
{
	if (*texture != NULL)
	{
		printf("Error\n duplicate texture defined\n");
		return (1);
	}
	line += 2; 
	while (*line == ' ')
		line++;
	*texture = ft_strdup(line);
	if (!*texture)
		return (1);
	remove_newline(*texture);
	if (check_file_access(*texture))
	{
		free(*texture);
		*texture = NULL;
		return(1);
	}
	return (0);
}

int	fill_color(int *color, char *line)
{
	char	**parts;
	int		rgb[3];

	if (*color != -1)
		return (printf("Error\nduplicate color defined\n"), 1);
	line++;
	while (*line == ' ')
		line++;
	parts = ft_split(line, ',');
	if (!parts)
		return (1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3]) 
	{
		// todo, free array func
		return (printf("Error\nInvalid color format\n"), 1);
	}
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	// also todo free parts array here
	if (check_rgb_values(rgb))
		return (1);
	// convert to hex
	*color= (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (0);
}
