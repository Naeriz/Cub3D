/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:23:19 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/08 13:38:03 by amezoe           ###   ########.fr       */
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
