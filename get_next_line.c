/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:37 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/18 17:59:04 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_and_store(int fd, char **line, int *size, int *len)
{
	char	buffer;
	int		read_bytes;

	read_bytes = read(fd, &buffer, 1);
	while (read_bytes > 0)
	{
		(*line)[(*len)] = buffer;
		(*len)++;
		if (buffer == '\n')
			break ;
		if (*len >= *size)
		{
			*size *= 2;
			*line = resize_buffer(*line, *len, *size);
			if (*line == NULL)
			{
				free (*line);
				return (-1);
			}
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
/*Variables:
> line: current line being read;
> size: current allocated size for the line buffer;
> len: current length of the line being read (position in the line);
> read_bytes: number of bytes read each time the function is called (0 or 1);

Implementation:
> Checks if the file descriptor (fd) is invalid or if BUFFER_SIZE is <= 0. If so,
	returns NULL.
> Sets the value of size to BUFFER_SIZE.
> Allocates memory for the line buffer with an initial size of BUFFER_SIZE
	+ 1 to accommodate the characters read.
> If allocation fails, returns NULL.
> Calls the function read_and_store:
	> Reads one character at a time, storing it in the line buffer,
		and increments the len index each time.
	> The read function returns the number of bytes read. If it returns 0,
		no bytes were read (end of file).
	> While any bytes are read,
		it assigns the value of line[len] to that character.
	> If the character is '\n', it breaks the loop,
		indicating the end of the line.
	> If len reaches the current size of the buffer,
		it "requests" more space for the next character:
		> Doubles the size by calling the resize_buffer function
			to allocate more space.
		> Creates a new buffer,
			copies the characters from the old buffer to the new buffer,
			and frees the old buffer.
	> Continues reading the next byte.
	> Keeps reading until read_bytes is 0 (end of file,
		no bytes to read) or a newline character is encountered.

> When no more bytes are read or it reaches the last position of the buffer,
	it terminates the line with '\0'.
> If no characters were read and the end of the file is reached (len is 0),
	it frees the line and returns NULL.
> Otherwise, it returns the line that was read. */
