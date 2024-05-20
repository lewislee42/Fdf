/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:48:50 by lewlee            #+#    #+#             */
/*   Updated: 2023/06/06 14:23:33 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnljoin(char *str1, char *str2)
{
	int		i;
	int		len1;
	char	*r_str;

	i = 0;
	len1 = gnlstrlen(str1);
	if (!str1)
	{
		str1 = (char *)malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	r_str = (char *)malloc((len1 + gnlstrlen(str2) + 1) * sizeof(char));
	if (!r_str)
	{
		free(str1);
		return (NULL);
	}
	while (i++ < len1)
		r_str[i - 1] = str1[i - 1];
	i = 0;
	while (str2[i++])
		r_str[i - 1 + len1] = str2[i - 1];
	r_str[i - 1 + len1] = '\0';
	free(str1);
	return (r_str);
}

char	*gnltrim(char *s)
{
	int		i;
	int		len;
	char	*r_str;

	i = -1;
	len = 0;
	if (!s || s[0] == '\0')
		return (NULL);
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	r_str = (char *)malloc((len + 2) * sizeof(char));
	if (!r_str)
		return (NULL);
	r_str[len] = '\0';
	while (++i < len)
		r_str[i] = s[i];
	return (r_str);
}

char	*gnlend(char *s)
{
	size_t	i;
	int		j;
	char	*r_str;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	r_str = (char *)malloc((gnlstrlen(s) - i + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	i++;
	j = 0;
	while (i < gnlstrlen(s))
		r_str[j++] = s[i++];
	r_str[j] = '\0';
	free(s);
	return (r_str);
}

char	*read_buff(int fd, char *res)
{
	char	*buffer;
	int		read_out;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_out = 1;
	while (!gnlstrchr(res, '\n') && read_out != 0)
	{
		read_out = read(fd, buffer, BUFFER_SIZE);
		if (read_out < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_out] = '\0';
		res = gnljoin(res, buffer);
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = read_buff(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = gnltrim(buffer[fd]);
	buffer[fd] = gnlend(buffer[fd]);
	return (line);
}