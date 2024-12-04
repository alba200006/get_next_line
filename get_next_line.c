/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-le <adiaz-le@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:43:50 by adiaz-le          #+#    #+#             */
/*   Updated: 2024/12/04 18:49:33 by adiaz-le         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	readed;
	int i = 0;

	temp_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	readed = 1;
	while (readed > 0 && !ft_strchr(temp_buffer, '\n'))
	{
		printf("Paso\n");
		readed = read(fd, temp_buffer, BUFFER_SIZE);
		printf("He leido %zu\n", readed > 0);
		if (readed < 0)
			return (free(buffer), buffer = NULL, free(temp_buffer), NULL);
		temp_buffer[readed] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		if (!buffer)
			return (free(temp_buffer), NULL);
		i++;
	}
	free(temp_buffer);
	return (buffer);
}

static char	*get_line_from_buffer(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		line = (char *)ft_calloc(i + 2, 1);
	else
		line = (char *)ft_calloc(i + 1, 1);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*newbuffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = (char *)ft_calloc(ft_strlen(buffer) - i, 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_from_buffer(buffer);
	if (!line)
		return (NULL);
	buffer = newbuffer(buffer);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int i = 10;
	int fd = open("hola.txt", O_RDONLY);
	char *line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}
