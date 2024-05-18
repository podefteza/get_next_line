/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:35 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/18 13:29:17 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*resize_buffer(char *buffer, int old_size, int new_size)
{
	char	*new_buffer;
	int		i;

	new_buffer = (char *)malloc(new_size * sizeof(char));
	if (new_buffer == NULL)
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
