/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:33:48 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/02 14:35:48 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			if (!ft_strchr("01NSEW ", data->map[i][j]))
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