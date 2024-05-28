/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:51:22 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/28 19:51:40 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total_size;
	size_t	i;

	total_size = nmemb * size;
	mem = malloc(total_size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dest == NULL) && (src == NULL))
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	free(s1);
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s) + 1;
	while (len > 0)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
		len--;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
