/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:40:04 by amezoe            #+#    #+#             */
/*   Updated: 2024/12/19 08:13:27 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_update_static(char *s, int fd, char *buffer)
{
	int	n;

	n = 1;
	while (ft_strchr(s, '\n') == NULL && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(s);
			return (NULL);
		}
		buffer[n] = '\0';
		s = ft_strjoin(s, buffer);
		if (!s)
			return (NULL);
	}
	return (s);
}

char	*ft_read(char *s, int fd)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	s = read_and_update_static(s, fd, buffer);
	free(buffer);
	return (s);
}

char	*ft_changing_static(char *s)
{
	char	*newstring;
	size_t	j;
	size_t	i;

	if (!s || !*s)
		return (free(s), NULL);
	j = 0;
	while (s[j] && s[j] != '\n')
		j++;
	if (!s[j])
		return (free(s), NULL);
	newstring = (char *)malloc((ft_strlen(s) - j) * sizeof(char));
	if (!newstring)
		return (free(s), NULL);
	i = 0;
	while (s[++j])
		newstring[i++] = s[j];
	newstring[i] = '\0';
	return (free(s), newstring);
}

char	*ft_get_line(char *result)
{
	char	*line;
	size_t	j;
	size_t	i;

	j = 0;
	if (result[0] == '\0')
		return (NULL);
	while (result[j] != '\n' && result[j] != '\0')
		j++;
	if (result[j] == '\n')
		j++;
	line = (char *)malloc(sizeof(char) * j + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < j)
	{
		line[i] = result[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_read(s, fd);
	if (s == NULL)
	{
		free (s);
		return (NULL);
	}
	buffer = ft_get_line(s);
	s = ft_changing_static(s);
	return (buffer);
}

// int main(void)
// {
// 	int fd;
// 	char *next_line;
// 	int count;
// 	fd = open("test.txt", O_RDONLY);
// 	count = 0;
// 	while ((next_line = get_next_line(fd)))
// 	{
// 		count++;
// 		printf("[%d]:%s", count, next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }