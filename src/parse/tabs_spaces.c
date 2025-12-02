/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:43:22 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/02 14:53:30 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//calc the length wwhen tabs are replaced w spaces
int	get_expanded_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

//alloc new string wire tab is replaced and frees the prev string
char	*expand_tabs(char *line)
{
	char	*new_line;
	int		len;
	int		i;
	int		j;

	len = get_expanded_len(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	free(line); //free the tabbed version
	return (new_line);
}
