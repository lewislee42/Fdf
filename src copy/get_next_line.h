/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:51:12 by lewlee            #+#    #+#             */
/*   Updated: 2023/06/06 14:23:03 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*gnljoin(char *str1, char *str2);
char	*gnltrim(char *s);
char	*gnlend(char *s);
char	*read_buff(int fd, char *res);
char	*gnlstrchr(const char *str, int c);
size_t	gnlstrlen(const char *s);
size_t	gnlstrlcpy(char *dest, const char *src, size_t size);

#endif