/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:35 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/29 10:51:34 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Calculates the length of string */
int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/* Allocates memory for an array of nmemb elements of size bytes each
   and initializes all bytes in the allocated storage to zero */
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

/* Copies n bytes from memory area src to memory area dest */
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

/* Allocates and returns a new string, which is the concatenation of
	s1 and s2 */
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

/* Locates the first occurrence of c in the string s */
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
