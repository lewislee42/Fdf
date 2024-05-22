/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 01:15:27 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/19 01:15:27 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_keys(t_main_info *main_info) {
	// init rotation keys
	main_info->keys.rotation.i = false;
	main_info->keys.rotation.j = false;
	main_info->keys.rotation.o = false;
	main_info->keys.rotation.k = false;
	main_info->keys.rotation.p = false;
	main_info->keys.rotation.l = false;

	// init movement keys
	main_info->keys.movement.w = false;
	main_info->keys.movement.s = false;
	main_info->keys.movement.a = false;
	main_info->keys.movement.d = false;

	// init scaling keys
	main_info->keys.scaling.q = false;
	main_info->keys.scaling.e = false;
}

static int	find_average_height(t_main_info *main_info) {
	int i = 0;
	int j = 0;
	int highest = 0;
	int lowest = 0;
	while (i < main_info->map_y) {
		j = 0;
		while (j < main_info->map_x) {
			if (lowest > main_info->map[i][j]) {
				lowest = main_info->map[i][j];
			}
			else if (highest < main_info->map[i][j]) {
				highest = main_info->map[i][j];
			}
			j++;
		}
		i++;
	}
	return ((highest + lowest) / 2);
}

// TODO: do error handling when malloc fails
// height map needs changing
void	init_pos(t_main_info *main_info) {
	int i = 0;
	int j = 0;
	main_info->points = malloc(sizeof(t_vec3 *) * (main_info->map_y));
	main_info->screen_post_calc = malloc(sizeof(t_vec3 *) * (main_info->map_y));
	while (i < main_info->map_y) {
		j = 0;
		main_info->points[i] = malloc(sizeof(t_vec3) * (main_info->map_x));
		main_info->screen_post_calc[i] = malloc(sizeof(t_vec3) * (main_info->map_x));
		while (j < main_info->map_x) {
			main_info->points[i][j].x = j * 0.1;
			main_info->points[i][j].y = i * 0.1;
			main_info->points[i][j].z = main_info->map[i][j] * 0.1;
			j++;
		}
		i++;
	}
}

void	init_matrices(t_main_info *main_info) {
	// // Calculate the tangent of half the field of view
	// float fov = 90.0f; // 90 degrees
	// float tanHalfFov = tanf(fov / 2.0f);

	// Define the aspect ratio (width / height) of the viewport
	// float aspectRatio = main_info->screen_width / main_info->screen_height;

	// // Define the near and far clipping planes
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// initializes projection matrix
			main_info->projectionMatrix[i][j] = 0.0f;

			// initializes rotation matrix
			main_info->rotationMatrix[i][j] = 0.0f;

			// initializes X Y Z rotation matrix
			main_info->xRotationMatrix[i][j] = 0.0f;
			main_info->yRotationMatrix[i][j] = 0.0f;
			main_info->zRotationMatrix[i][j] = 0.0f;

			// initializes scaling matrix
			main_info->scalingMatrix[i][j] = 0.0f;

			// initializes translation matrix
			main_info->translationOrigin[i][j] = 0.0f;
			main_info->translationBack[i][j] = 0.0f;
		}
	}

	float left = -1.0f, right = 1.0f, bottom = -1.0f, top = 1.0f;
	main_info->projectionMatrix[0][0] = 2 / (right - left);
	main_info->projectionMatrix[0][3] = -(right + left) / (right - left);
	main_info->projectionMatrix[1][1] = 2 / (top - bottom);
	main_info->projectionMatrix[1][3] = -(top + bottom) / (top - bottom);

	main_info->projectionMatrix[2][2] = -2 / (farPlane - nearPlane);
	main_info->projectionMatrix[2][3] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	main_info->projectionMatrix[3][3] = 1.0f;

	// with perspective
	// main_info->projectionMatrix[0][0] = aspectRatio * (1 / tanHalfFov);
	// main_info->projectionMatrix[1][1] = 1.0f / tanHalfFov;
	// main_info->projectionMatrix[2][2] = farPlane / (farPlane - nearPlane);
	// main_info->projectionMatrix[2][3] = (-farPlane * nearPlane) / (farPlane - nearPlane);
	// main_info->projectionMatrix[3][2] = 1.0f;

	main_info->rotationMatrix[0][0] = 1.0f;
	main_info->rotationMatrix[1][1] = 1.0f;
	main_info->rotationMatrix[2][2] = 1.0f;
	main_info->rotationMatrix[3][3] = 1.0f;

	main_info->scalingMatrix[0][0] = 1.0f;
	main_info->scalingMatrix[1][1] = 1.0f;
	main_info->scalingMatrix[2][2] = 1.0f;
	main_info->scalingMatrix[3][3] = 1.0f;

	main_info->center.x = main_info->points[main_info->map_y / 2][main_info->map_x / 2].x;
	main_info->center.y = main_info->points[main_info->map_y / 2][main_info->map_x / 2].y;
	// main_info->center.z = main_info->points[main_info->map_y / 2][main_info->map_x / 2].z;
	main_info->center.z = (float)(find_average_height(main_info) * 0.1);

	main_info->translationOrigin[0][0] = 1.0f;
	main_info->translationOrigin[0][3] = -main_info->center.x;
	main_info->translationOrigin[1][1] = 1.0f;
	main_info->translationOrigin[1][3] = -main_info->center.y;
	main_info->translationOrigin[2][2] = 1.0f;
	main_info->translationOrigin[2][3] = -main_info->center.z;
	main_info->translationOrigin[3][3] = 1.0f;

	main_info->translationBack[0][0] = 1.0f;
	main_info->translationBack[0][3] = main_info->center.x;
	main_info->translationBack[1][1] = 1.0f;
	main_info->translationBack[1][3] = main_info->center.y;
	main_info->translationBack[2][2] = 1.0f;
	main_info->translationBack[2][3] = main_info->center.z;
	main_info->translationBack[3][3] = 1.0f;
}
