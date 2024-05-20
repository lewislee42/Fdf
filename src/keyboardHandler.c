/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboardHandler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 01:05:49 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/19 01:05:49 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scaling_keyhandler(SDL_Event event, t_main_info *main_info, bool type) {
	if (event.key.keysym.sym == SDLK_q)
		main_info->keys.scaling.q = type;
	if (event.key.keysym.sym == SDLK_e)
		main_info->keys.scaling.e = type;
}

void	rotation_keyhandler(SDL_Event event, t_main_info *main_info, bool type) {
	// x axis
	if (event.key.keysym.sym == SDLK_i)
		main_info->keys.rotation.i = type;
	if (event.key.keysym.sym == SDLK_j)
		main_info->keys.rotation.j = type;

	// y axis
	if (event.key.keysym.sym == SDLK_o)
		main_info->keys.rotation.o = type;
	if (event.key.keysym.sym == SDLK_k)
		main_info->keys.rotation.k = type;

	// z axis
	if (event.key.keysym.sym == SDLK_p)
		main_info->keys.rotation.p = type;
	if (event.key.keysym.sym == SDLK_l)
		main_info->keys.rotation.l = type;
}

void	translate_handler(SDL_Event event, t_main_info *main_info, bool type) {
	// up down
	if (event.key.keysym.sym == SDLK_w)
		main_info->keys.movement.w = type;
	if (event.key.keysym.sym == SDLK_s)
		main_info->keys.movement.s = type;

	// left right
	if (event.key.keysym.sym == SDLK_a)
		main_info->keys.movement.a = type;
	if (event.key.keysym.sym == SDLK_d)
		main_info->keys.movement.d = type;
}