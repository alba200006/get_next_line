#include "get_next_line.h"

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	readed;
	char	*temp;

	temp_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	readed = 1;
	while (!ft_strchr(buffer, '\n') && readed > 0)
	{
		readed = read(fd, temp_buffer, BUFFER_SIZE);
		if (readed < 0)
			return (free(temp_buffer), free(buffer), NULL);
		if (readed == 0)
			break ;
		temp_buffer[readed] = '\0';
		temp = ft_strjoin(buffer, temp_buffer);
		if (!temp)
			return (free(temp_buffer), NULL);
		buffer = temp;
	}
	free(temp_buffer);
	if (readed == 0 && (!buffer || *buffer == '\0'))
		return (free(buffer), NULL);
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
		return (free(buffer), NULL);
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

static char	*newbuffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = (char *)ft_calloc(ft_strlen(buffer) - i, 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_from_buffer(buffer);
	if (!line)
		return (NULL);
	buffer = newbuffer(buffer);
	return (line);
}

// int main(void)
// {
//     int fd = open("hola", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error al abrir el archivo");
//         return (1);
//     }

//     char *line = get_next_line(fd);
//     while (line)
//     {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }