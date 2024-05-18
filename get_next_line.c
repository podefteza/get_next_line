/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:37 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/18 11:56:13 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*resize_buffer(char *buffer, int old_size, int new_size)
{
	char	*new_buffer;
	int		i;

	new_buffer = (char *)malloc(new_size * sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

int	read_and_store(int fd, char **line, int *size, int *len)
{
	char	buffer;
	int		read_bytes;

	read_bytes = read(fd, &buffer, 1);
	while (read_bytes > 0)
	{
		(*line)[(*len)++] = buffer;
		if (buffer == '\n')
			break ;
		if (*len >= *size)
		{
			*size *= 2;
			*line = resize_buffer(*line, *len, *size);
			if (*line == NULL)
				return (-1);
		}
		read_bytes = read(fd, &buffer, 1);
	}
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		size;
	int		len;
	int		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	size = BUFFER_SIZE;
	line = (char *)malloc((size + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	len = 0;
	read_bytes = read_and_store(fd, &line, &size, &len);
	if (read_bytes < 0 || (read_bytes == 0 && len == 0))
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}

/* ===== MAIN FOR TESTING... =====

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("cat.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}*/

/* ===== test.txt FOR TESTING... =====
Lorem ipsum dolor sit amet, consectetur adipiscing elit.

Praesent scelerisque at nunc non ornare.

Nullam eget tempus lacus. Lorem ipsum dolor sit amet,
consectetur adipiscing elit.

Pellentesque habitant morbi tristique senectus et netus
et malesuada fames ac turpis egestas.

Sed at mi. */
