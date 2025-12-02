/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:19 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/02 14:57:43 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

//free the tecture path and texture struct
void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	free(textures);
}

//free map,texture and close fd if open
void	free_data(t_map *data)
{
	if (data->textures)
		free_textures(data->textures);
	if (data->map)
		free_tab(data->map);
	//just a double check if an error happens before parsemap happens, not sure if we have to we will see
	// if (data->fd > 0)
	// 	close(data->fd); 
}

int	exit_error(t_map *data, char *msg)
{
	free_data(data);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
	return (1);
}