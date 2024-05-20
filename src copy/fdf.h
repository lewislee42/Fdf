/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:34:01 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/06 21:34:01 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// normal includes
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

// gnl
# include "get_next_line.h"

// SDL
# define SDL_MAIN_HANDLED
# include <SDL.h>

typedef struct s_pos {
	float	x;
	float	y;
	float	z;
}	t_pos;

typedef struct s_main_info {
	char 			**map;
	struct s_pos	**points;
	int				map_x;
	int				map_y;
	unsigned int	colorHigh;
	unsigned int	colorLow;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				error_code;
	bool			is_running;
}	t_main_info;





// utils.c
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	*ft_strchr(const char *str, int c);

#endif