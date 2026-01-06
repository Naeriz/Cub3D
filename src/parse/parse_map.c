/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:23:22 by amezoe            #+#    #+#             */
/*   Updated: 2026/01/06 14:05:51 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_max_width(t_list *map_list)
{
	int		max;
	int		len;
	t_list	*curr;

	max = 0;
	curr = map_list;
	while (curr)
	{
		len = ft_strlen((char *)curr->content);
		if (((char *)curr->content)[len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		curr = curr->next;
	}
	return (max);
}

void	get_player_pos(t_map *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NESW", data->map[y][x]))
			{
				data->player_x = (double)x + 0.5;
				data->player_y = (double)y + 0.5;
				data->player_dir = data->map[y][x];
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	list_to_array(t_map *data, t_list *map_list)
{
	int		i;
	t_list	*curr;

	data->height = ft_lstsize(map_list);
	data->width = get_max_width(map_list);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (1);
	curr = map_list;
	i = 0;
	while (curr)
	{
		data->map[i] = process_map_line((char *)curr->content);
		if (!data->map[i])
		{
			data->map[i] = NULL;
			free_tab(data->map);
			return (1);
		}
		curr = curr->next;
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

void	read_map_loop(int fd, t_list **map_list)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_lstadd_back(map_list, ft_lstnew(line));
	}
}

int	parse_map(t_map *data, char *first_line)
{
	t_list	*map_list;

	map_list = NULL;
	ft_lstadd_back(&map_list, ft_lstnew(first_line));
	read_map_loop(data->fd, &map_list);
	close(data->fd);
	data->fd = -1;
	if (list_to_array(data, map_list))
	{
		ft_lstclear(&map_list, free);
		return (1);
	}
	ft_lstclear(&map_list, free);
	if (validate_map_content(data))
	{
		free_tab(data->map);
		data->map = NULL;
		return (1);
	}
	return (0);
}
