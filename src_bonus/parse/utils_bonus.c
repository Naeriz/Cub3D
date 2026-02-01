/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 07:44:50 by amezoe            #+#    #+#             */
/*   Updated: 2026/02/01 12:25:59 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

void	remove_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == '\n' || str[i] == '\r'
			|| str[i] == ' ' || str[i] == '\t'))
	{
		str[i] = '\0';
		i--;
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
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*texture = ft_strdup(line);
	if (!*texture)
		return (1);
	remove_newline(*texture);
	if (check_file_access(*texture))
	{
		free(*texture);
		*texture = NULL;
		return (1);
	}
	return (0);
}

int	fill_color(int *color, char *line)
{
	char	**parts;
	int		rgb[3];

	if (*color != -1)
		return (printf("Error\nDuplicate color defined\n"), 1);
	line++;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	parts = ft_split(line, ',');
	if (!parts)
		return (1);
	if (parse_rgb_parts(parts, rgb) || check_rgb_values(rgb))
	{
		free_tab(parts);
		return (printf("Error\nInvalid color format or value\n"), 1);
	}
	free_tab(parts);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (0);
}
