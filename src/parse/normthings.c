/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normthings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:21:57 by amezoe            #+#    #+#             */
/*   Updated: 2026/02/06 16:56:55 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	longest_line(char **map, int height)
{
	int	i;
	int	longest;
	int	len;

	i = 0;
	longest = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

void	fill_new_row(char *new_row, char *old, int width)
{
	int	j;

	j = 0;
	while (old[j])
	{
		if (old[j] == ' ')
			new_row[j] = '1';
		else
			new_row[j] = old[j];
		j++;
	}
	while (j < width)
	{
		new_row[j] = '1';
		j++;
	}
	new_row[j] = '\0';
}

char	**alloc_square(t_map *data)
{
	char	**new_map;
	int		i;

	data->width = longest_line(data->map, data->height);
	new_map = malloc(sizeof(char *) * (data->height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		new_map[i] = malloc(sizeof(char) * (data->width + 1));
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free (new_map[i]);
			return (NULL);
		}
		fill_new_row(new_map[i], data->map[i], data->width);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	make_it_square(t_map *data)
{
	char	**new_map;

	new_map = alloc_square(data);
	if (!new_map)
		return (1);
	free_tab(data->map);
	data->map = new_map;
	return (0);
}
