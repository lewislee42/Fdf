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
# include <math.h>
# include <string.h>

// gnl
# include "get_next_line.h"

// SDL
# define SDL_MAIN_HANDLED
# include <SDL.h>

typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4 {
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_movement_keys {
	bool	w;
	bool	s;
	bool	a;
	bool	d;
}	t_movement_keys;

typedef struct s_rotation_keys {
	bool	i;
	bool	j;
	bool	o;
	bool	k;
	bool	p;
	bool	l;
}	t_rotation_keys;

typedef struct s_scaling_keys {
	bool	q;
	bool	e;
}	t_scaling_keys;

typedef struct s_keys {
	struct s_movement_keys		movement;
	struct s_rotation_keys		rotation;
	struct s_scaling_keys		scaling;
}	t_keys;

typedef struct s_file_lst {
	char	*s;
	struct s_file_lst	*next;
	struct s_file_lst	*prev;
}	t_file_lst;

typedef struct s_main_info {
	int 			**map;
	struct s_vec3	**points;
	struct s_vec3	**screen_post_calc;
	int				map_x;
	int				map_y;
	
	struct s_keys	keys;

	// translation matrix
	struct s_vec3	pos;
	struct s_vec3	center;
	float			translationMatrix[4][4];
	float			translationOrigin[4][4];
	float			translationBack[4][4];
	
	// scaling matrix
	float			scale;
	float			scalingMatrix[4][4];

	// rotation matrix
	float			xAngle;
	float			yAngle;
	float			zAngle;
	float			xRotationMatrix[4][4];
	float			yRotationMatrix[4][4];
	float			zRotationMatrix[4][4];
	float			rotationMatrix[4][4];

	float			projectionMatrix[4][4];
	int				screen_width;
	int				screen_height;

	unsigned int	colorHigh;	// not yet implemented
	unsigned int	colorLow;	// not yet implemented
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
void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *nb);
void	multiplyMatrix(float a[4][4], float b[4][4], float result[4][4]);
void	matrix_multiply(float projection_matrix[4][4], t_vec4 *pos);
t_vec4	orthographic(t_main_info *main_info, float matrix[4][4], int i, int j);

// update.c
void	update_scaleMatrix(float scalingMatrix[4][4], float scale);
void	update_xMatrix(float xMatrix[4][4], float angle);
void	update_yMatrix(float yMatrix[4][4], float angle);
void	update_zMatrix(float zMatrix[4][4], float angle);
void	update_translate(t_main_info *main_info);
void	update_angle(t_main_info *main_info);
void	update_scale(t_main_info *main_info);
void	update_center(t_main_info *main_info);

// keyboardHandler.c
void	scaling_keyhandler(SDL_Event event, t_main_info *main_info, bool type);
void	rotation_keyhandler(SDL_Event event, t_main_info *main_info, bool type);
void	translate_handler(SDL_Event event, t_main_info *main_info, bool type);

// init.c
void	init_keys(t_main_info *main_info);
void	init_matrices(t_main_info *main_info);
void	init_pos(t_main_info *main_info);

// map_init.c
int		validate_input(char **argv, t_main_info *main_info);

// file_lst.c
void		ft_file_lstclear(t_file_lst **lst, void (*del)(void*));
void		ft_file_lstadd_back(t_file_lst **lst, t_file_lst *new);
t_file_lst	*ft_file_lstlast(t_file_lst *lst);
int			ft_file_lstsize(t_file_lst *lst);
t_file_lst	*create_filenode(char *s);

#endif