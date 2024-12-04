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

	temp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, temp_buffer, BUFFER_SIZE);
		if (readed < 0)
			return (free(buffer), buffer = NULL, free(temp_buffer), NULL);
		temp_buffer[readed] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		if (!buffer)
			return (free(temp_buffer), NULL);
	}
	free (temp_buffer);
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
		line = (char *)malloc(i + 2);
	else
		line = (char *)malloc(i + 1);
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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*new_buffer;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	if (buffer && buffer[0] == '\0')
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_from_buffer(buffer);
	if (!line)
		return (NULL);
	if (ft_strlen(buffer) == ft_strlen(line))
		return (free(buffer), buffer = "\0", line);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = (char *)malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	return (new_buffer[j] = '\0', free(buffer), buffer = new_buffer, line);
}
