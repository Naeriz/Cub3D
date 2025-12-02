/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:23:22 by amezoe            #+#    #+#             */
/*   Updated: 2025/12/02 14:51:43 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// plan here is that ill read the lines to a linked list
// count the nodes and then malloc data->map (char**) then copy
// the strings from the list to the array, so we should
// be able to malloc it w no issues
//i also need to add the extra libft functions for the list lol

//iterates the list to find the longest line this will add the data->width
int get_max_width(t_list *map_list)
{
	int		max;
	int		len;
	t_list	*curr;
	
	max = 0;
	curr = map_list;
	while (curr)
	{
		len = ft_strlen((char *)curr->content);
		if (((char *)curr->content)[len-1] == '\n') //if map has \n at end, dont count it in width
			len--;
		if (len > max)
			max = len;
		curr = curr->next;
	}
	return (max);
}

//check the map for the directions and sets the player x y and dir
//replacing NESW with 0 so player can walk on it

void get_player_pos(t_map *data)
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

//allocates the char** array and copies the strings from the list
int	list_to_array(t_map *data, t_list *map_list)
{
	int		i;
	t_list	*curr;
	char	*temp;

	data->height = ft_lstsize(map_list);
	data->width = get_max_width(map_list);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (1);
	curr = map_list;
	i = 0;
	while (curr)
	{
		temp = ft_strdup((char *)curr->content);
		if (!temp)
			return (1);
		remove_newline(temp);
		//expand_tabs frees temp inside it so we don't leak
		data->map[i] = expand_tabs(temp);
		if (!data->map[i])
			return (1);
		curr = curr->next;
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	parse_map(t_map *data, char *first_line)
{
	t_list	*map_list;
	char	*line;

	map_list = NULL;
	ft_lstadd_back(&map_list, ft_lstnew(first_line));
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		ft_lstadd_back(&map_list, ft_lstnew(line));
	}
	close(data->fd);
	if (list_to_array(data, map_list))
	{
		ft_lstclear(&map_list, free);
		return (1);
	}
	ft_lstclear(&map_list, free);
	if (check_map_validity(data))
		return (1);
	get_player_pos(data);
	return (0);
}

