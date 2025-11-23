/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 07:44:50 by amezoe            #+#    #+#             */
/*   Updated: 2025/11/23 08:04:53 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


//placeholder for now, todo later
//skip the direction, trim \n then dup the path 
int	fill_texture_path(char **texture, char *line)
{
	(void)texture;
	(void)line;
	printf("Found texture line: %s", line);
	return (0);
}

//also placeholder, have to parse the actual rgb codes
int	fill_color(int *color, char *line)
{
	(void)color;
	(void)line;
	printf("Found color line: %s", line);
	return (0);
}