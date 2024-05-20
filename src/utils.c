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

void	*ft_memset(void *s, int c, size_t n)
{
	char	*val;

	val = s;
	while (n--)
	{
		*val++ = c;
	}
	return (s);
}

void multiplyMatrix(float a[4][4], float b[4][4], float result[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrix_multiply(float projection_matrix[4][4], t_vec4 *pos) {
	t_vec4 res;

    // Multiply the matrices
	res.x = 0.0f;
	res.y = 0.0f;
	res.z = 0.0f;
	res.w = 0.0f;

	res.x = pos->x * projection_matrix[0][0] + pos->y * projection_matrix[0][1] + pos->z * projection_matrix[0][2] + pos->w * projection_matrix[0][3];
	res.y = pos->x * projection_matrix[1][0] + pos->y * projection_matrix[1][1] + pos->z * projection_matrix[1][2] + pos->w * projection_matrix[1][3];
	res.z = pos->x * projection_matrix[2][0] + pos->y * projection_matrix[2][1] + pos->z * projection_matrix[2][2] + pos->w * projection_matrix[2][3];
	res.w = pos->x * projection_matrix[3][0] + pos->y * projection_matrix[3][1] + pos->z * projection_matrix[3][2] + pos->w * projection_matrix[3][3];

	pos->x = res.x;
	pos->y = res.y;
	pos->z = res.z;
	pos->w = res.w;

	// DEBUGGING
	// for (int i = 0; i < 4; i++) {
	// 	for (int j = 0; j < 4; j++) {
	// 		printf("%f ", projection_matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("NDC_x: %f | NDC_y: %f | NDC_z: %f | NDC_w: %f\n", res.x, res.y, res.z, res.w);
}

// TODO: add function for matrix multiplication
t_vec4	orthographic(t_main_info *main_info, float matrix[4][4], int i, int j) {
	// Multiply the 3D coordinates by the projection matrix
	t_vec4 result = (t_vec4){main_info->points[i][j].x, main_info->points[i][j].y, main_info->points[i][j].z, 1.0f};

	matrix_multiply(main_info->translationOrigin, &result);
	matrix_multiply(main_info->scalingMatrix, &result);
	matrix_multiply(main_info->rotationMatrix, &result);
	matrix_multiply(main_info->translationBack, &result);
	matrix_multiply(matrix, &result);
	return (result);
}

// t_vec4	perspective(t_main_info *main_info, float matrix[4][4], int i, int j) {
// 	// Multiply the 3D coordinates by the projection matrix
// 	t_vec4 result = (t_vec4){main_info->points[i][j].x, main_info->points[i][j].y, main_info->points[i][j].z, 1.0f};

// 	// printf("pos: x : %f | x : %f | x : %f\n", main_info->pos.x, main_info->pos.y, main_info->pos.z);
// 	matrix_multiply(main_info->translationOrigin, &result);
// 	matrix_multiply(main_info->scalingMatrix, &result);
// 	matrix_multiply(main_info->rotationMatrix, &result);
// 	matrix_multiply(main_info->translationBack, &result);
// 	matrix_multiply(matrix, &result);

// 	// Perform perspective divide
// 	if (result.w != 0) {
// 		result.x /= result.w;
// 		result.y /= result.w;
// 		result.z /= result.w;

// 		// DEBUGGING
// 		// printf("pos.x: %f | pos.y: %f | pos.z: %f\n", main_info->points[i][j].x, main_info->points[i][j].y, main_info->points[i][j].z);
// 		// printf("NDC_x: %f | NDC_y: %f | NDC_z: %f\n", result.x, result.y, result.z);
// 	}
// 	return (result);
// }