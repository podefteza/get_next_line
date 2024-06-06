/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:46:11 by carlos-j          #+#    #+#             */
/*   Updated: 2024/06/06 10:28:57 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = newline_index;
	while ((*buffer)[j])
	{
		(*buffer)[i] = (*buffer)[j];
		i++;
		j++;
	}
	(*buffer)[i] = '\0';
	new_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (new_buffer == NULL)
		return ;
	i = 0;
	while ((*buffer)[i])
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	free(*buffer);
	*buffer = new_buffer;
}

static int	handle_read_error(char **buffer, char *temp_buf)
{
	free(temp_buf);
	free(*buffer);
	*buffer = NULL;
	return (-1);
}

static int	read_and_append(int fd, char **buffer)
{
	char	*temp_buf;
	int		bytes_read;

	temp_buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (temp_buf == NULL)
		return (-1);
	while (ft_strchr(*buffer, '\n') == NULL)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (handle_read_error(buffer, temp_buf));
		if (bytes_read == 0)
			break ;
		temp_buf[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, temp_buf);
		if (*buffer == NULL)
		{
			free(temp_buf);
			return (-1);
		}
	}
	free(temp_buf);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1042];
	int			newline_index;
	char		*line;

	if (fd < 0 || fd >= 1042 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer[fd] == NULL)
			return (NULL);
		buffer[fd][0] = '\0';
	}
	if (read_and_append(fd, &buffer[fd]) == -1)
		return (NULL);
	if (buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = get_line_from_buffer(&buffer[fd], &newline_index);
	update_buffer(&buffer[fd], newline_index);
	return (line);
}
/*
> The bonus version let's the program work with multiple fds at the same time;
> Instead of one static buffer for all fds, it uses an array of buffers, indexed
	by the fd number. This way we can work on each fd separately;
> We give it a size of 1042, the maximum number of open files simultaneously
	per process in Linux;
*/
