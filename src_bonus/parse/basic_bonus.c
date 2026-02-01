/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:23:19 by amezoe            #+#    #+#             */
/*   Updated: 2026/02/01 12:26:16 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	check_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (1);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	parse_args(t_map *map, char **av)
{
	if (check_extension(av[1]))
	{
		ft_putstr_fd("Error\n invalid file extension (must be .cub)\n", 2);
		return (1);
	}
	map->path = av[1];
	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
	{
		perror("Error\n cant open file");
		return (1);
	}
	return (0);
}

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	is_valid_num_str(char *str)
{
	int	i;
	int	digit_found;

	i = 0;
	digit_found = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		digit_found = 1;
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!digit_found || str[i] != '\0')
		return (0);
	return (1);
}

int	parse_rgb_parts(char **parts, int *rgb)
{
	int	i;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (1);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_num_str(parts[i]))
			return (1);
		rgb[i] = ft_atoi(parts[i]);
		i++;
	}
	return (0);
}
