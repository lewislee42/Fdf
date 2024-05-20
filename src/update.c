/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:06:27 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/18 19:06:27 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_scaleMatrix(float scalingMatrix[4][4], float scale) {
	scalingMatrix[0][0] = scale;
	scalingMatrix[1][1] = scale;
	scalingMatrix[2][2] = scale;
}

void	update_xMatrix(float xMatrix[4][4], float angle) {
	float	cosRes = cos(angle);
	float	sinRes = sin(angle);
	xMatrix[0][0] = 1.0f;
	xMatrix[1][1] = cosRes;
	xMatrix[1][2] = -sinRes;
	xMatrix[2][1] = sinRes;
	xMatrix[2][2] = cosRes;
	xMatrix[3][3] = 1.0f;
}

void	update_yMatrix(float yMatrix[4][4], float angle) {
	float	cosRes = cos(angle);
	float	sinRes = sin(angle);
	yMatrix[0][0] = cosRes;
    yMatrix[0][2] = sinRes;
    yMatrix[1][1] = 1.0f;
    yMatrix[2][0] = -sinRes;
    yMatrix[2][2] = cosRes;
    yMatrix[3][3] = 1.0f;
}

void	update_zMatrix(float zMatrix[4][4], float angle) {
	float	cosRes = cos(angle);
	float	sinRes = sin(angle);
	zMatrix[0][0] = cosRes;
	zMatrix[0][1] = -sinRes;
	zMatrix[1][0] = sinRes;
	zMatrix[1][1] = cosRes;
	zMatrix[2][2] = 1.0f;
	zMatrix[3][3] = 1.0f;
}

void	update_translate(t_main_info *main_info) {
	main_info->translationOrigin[0][3] = -main_info->center.x;
	main_info->translationOrigin[1][3] = -main_info->center.y;
	main_info->translationOrigin[2][3] = -main_info->center.z;

	main_info->translationBack[0][3] = main_info->center.x + main_info->pos.x;
	main_info->translationBack[1][3] = main_info->center.y + main_info->pos.y;
	main_info->translationBack[2][3] = main_info->center.z + main_info->pos.z;
}

void	update_center(t_main_info *main_info) {
	if (main_info->keys.movement.w == true) {
		// main_info->center.y += 0.0005f;
		main_info->pos.y += 0.0005f;
	}
	if (main_info->keys.movement.s == true) {
		// main_info->center.y -= 0.0005f; 
		main_info->pos.y -= 0.0005f;
	}
	if (main_info->keys.movement.d == true) {
		// main_info->center.x += 0.0005f; 
		main_info->pos.x += 0.0005f;
	}
	if (main_info->keys.movement.a == true) {
		// main_info->center.x -= 0.0005f; 
		main_info->pos.x -= 0.0005f;
	}
}

void	update_angle(t_main_info *main_info) {
	// x axis
	if (main_info->keys.rotation.i == true)
		main_info->xAngle += 0.0005f;
	if (main_info->keys.rotation.j == true)
		main_info->xAngle -= 0.0005f;

	// y axis
	if (main_info->keys.rotation.o == true)
		main_info->yAngle -= 0.0005f;
	if (main_info->keys.rotation.k == true)
		main_info->yAngle += 0.0005f;

	// z axis
	if (main_info->keys.rotation.p == true)
		main_info->zAngle -= 0.0005f;
	if (main_info->keys.rotation.l == true)
		main_info->zAngle += 0.0005f;
}

void	update_scale(t_main_info *main_info) {
	if (main_info->keys.scaling.q == true)
		main_info->scale += 0.0005f;
	if (main_info->scale - 0.0005f > 0.0005f && main_info->keys.scaling.e == true)
		main_info->scale -= 0.0005f;
}
