 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:37 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/28 21:27:51 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_from_buffer(char **buffer, int *newline_index)
{
	char	*line;
	int		i;
	int		line_length;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line_length = i;
	if ((*buffer)[i] == '\n')
		line_length++;
	line = (char *)ft_calloc(line_length + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < line_length)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[line_length] = '\0';
	*newline_index = line_length;
	return (line);
}

static void	update_buffer(char **buffer, int newline_index)
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
	static char	*buffer;
	int			newline_index;
	char		*line;

	if (fd < 0 || BUFFER_SIZE  <= 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
		buffer[0] = '\0';
	}
	if (read_and_append(fd, &buffer) == -1)
		return (NULL);
	if (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_line_from_buffer(&buffer, &newline_index);
	update_buffer(&buffer, newline_index);
	return (line);
}

/*
======== Variables ========
> buffer: stores the data read from the fd;
> newline_index: index of the \n character in the buffer (for splitting lines);
> line: line currently being read and returned by the function;
> i: index variable used for iterating through the buffer;
> line_length: length of the line being read,
	including the \n character if it exists;
> temp_buf: temporary buffer used for reading data from the fd;
> bytes_read: number of bytes read from the fd in each read operation.

======== Implementation ========
> Checks if the fd is valid and if BUFFER_SIZE is greater than 0. If not,
	returns NULL;
> Initializes the static buffer 'buffer' if it's not already initialized,
	allocating memory for it;
> Calls the read_and_append function:
	> Reads data from the fd into the temporary buffer 'temp_buf' until a
		\n character is encountered in the 'buffer';
	> If an error occurs during reading or memory allocation,
		handles the error and returns -1;
	> Appends the data from 'temp_buf' to the end of 'buffer' using ft_strjoin;
> Checks if 'buffer' is empty or NULL after reading and appending data. If so,
	frees the buffer and returns NULL;
> Extracts a line from 'buffer' using the get_line_from_buffer function:
	> Finds the index of the \n character in 'buffer';
	> Allocates memory for 'line' and copies the characters from 'buffer'
		up to the \n character, if present;
> Updates 'buffer' to remove the read line using the update_buffer function:
	> Shifts the contents of 'buffer' to remove the read line and updates
		'buffer' with the new content;
> Returns the extracted line read from the fd.
*/
