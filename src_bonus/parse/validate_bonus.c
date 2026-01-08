/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:33:48 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/08 13:38:29 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cub3d.h"

int	check_map_validity(t_map *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!ft_strchr("01NSEW D", data->map[i][j]))
				return (printf("Error\nInvalid character in map\n"), 1);
			if (ft_strchr("NSEW", data->map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error\nThere can be only one player\n"), 1);
	return (0);
}

int	validate_map_content(t_map *data)
{
	if (check_map_validity(data))
		return (1);
	if (check_doors(data))
		return (1);
	get_player_pos(data);
	if (check_walls(data))
		return (1);
	return (0);
}

char	*process_map_line(char *raw_cont)
{
	char	*tmp;
	char	*result;

	tmp = ft_strdup(raw_cont);
	if (!tmp)
		return (NULL);
	remove_newline(tmp);
	result = expand_tabs(tmp);
	if (!result)
		return (NULL);
	return (result);
}
