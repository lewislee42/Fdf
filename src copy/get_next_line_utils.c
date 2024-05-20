/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:51:32 by lewlee            #+#    #+#             */
/*   Updated: 2023/06/06 14:24:51 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnlstrlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnlstrchr(const char *str, int c)
{
	int	i;
	int	len;

	i = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return (NULL);
	len = gnlstrlen(str);
	while (i <= len)
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

size_t	gnlstrlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1 && size != 0)
	{
		if (size == 0)
			break ;
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}