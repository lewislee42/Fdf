/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:40:12 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/06 21:40:12 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s) {
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!string)
		return (NULL);
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

static int	len_finder(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_mstrdup(const char *str, int limit)
{
	char	*r_str;
	int		i;

	i = 0;
	r_str = malloc((limit + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	while (str[i] && i < limit)
	{
		r_str[i] = str[i];
		i++;
	}
	r_str[i] = '\0';
	return (r_str);
}

char	**ft_split(char const *s, char c)
{
	int		i[3];
	char	**r_str;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	r_str = malloc((len_finder(s, c) + 1) * sizeof(char *));
	if (!r_str)
		return (NULL);
	while (i[0] < (int)ft_strlen(s) + 1)
	{
		if ((s[i[0]] == c || s[i[0]] == '\0') && i[2] != 0)
		{
			r_str[i[1]++] = ft_mstrdup(s + (i[0] - i[2]), i[2]);
			i[2] = 0;
		}
		else if (s[i[0]] != c)
			i[2]++;
		i[0]++;
	}
	r_str[i[1]] = 0;
	return (r_str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// char	*ft_strchr(const char *str, int c)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(str);
// 	while (i <= len)
// 	{
// 		if (str[i] == (char)c)
// 			return ((char *)str + i);
// 		i++;
// 	}
// 	return (NULL);
// }