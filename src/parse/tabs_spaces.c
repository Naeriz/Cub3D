/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:43:22 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/06 14:01:22 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	space_from_tabs(char *new_line, char *line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			k = -1;
			while (++k < 4)
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
}

char	*expand_tabs(char *line)
{
	char	*new_line;
	int		len;

	len = get_expanded_len(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	space_from_tabs(new_line, line);
	free(line);
	return (new_line);
}
