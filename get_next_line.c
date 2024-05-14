/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:37 by carlos-j          #+#    #+#             */
/*   Updated: 2024/05/14 18:14:23 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// use only one static funcion to bonus
#include "get_next_line.h"

char	*get_next_line(int fd)
{

}

// read, malloc, free
/*Read line: correct behavior
NULL: there is nothing else to read, or an error
occurred*/

/*Read Byte by Byte and check that each byte against '\n' if it is not, then store it into buffer
if it is '\n' add '\0' to buffer and then use atoi()

You can read a single byte like this

char c;
read(fd,&c,1);*/
/*cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c*/
