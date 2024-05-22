/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:13:04 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/06 23:13:04 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

// TODO:
// 	need to add a freeing/cleanup function if the sdl_init fails
//	need to add a freeing/cleanup function if the window/renderer creation fails
int	setup(char **argv, t_main_info *main_info) {
	printf("Getting input file\n");
	if (validate_input(argv, main_info))
		return (1);

	init_pos(main_info);
	main_info->screen_width = 800;
	main_info->screen_height = 600;
	main_info->scale = 1.0f;

	main_info->xAngle = 0;
	main_info->yAngle = 0;
	main_info->zAngle = 0;
	main_info->pos = (t_vec3){0.0f, 0.0f, 1.0f};

	init_matrices(main_info);

	init_keys(main_info);

	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return (1);
    }
	main_info->window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, main_info->screen_width, main_info->screen_height, SDL_WINDOW_SHOWN);
	main_info->renderer = SDL_CreateRenderer(main_info->window, -1, 0);

	SDL_SetRenderDrawColor(main_info->renderer, 0, 0, 0, 255);

	SDL_RenderClear(main_info->renderer);

	SDL_RenderPresent(main_info->renderer);
	return (0);
}

void	cleanup(t_main_info *main_info) {
	SDL_DestroyWindow(main_info->window);
	SDL_Quit();
}

// TODO: need to do the boolean thing so that the movement wont stagger
void	process_input(t_main_info *main_info) {
	SDL_Event	event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			main_info->is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				main_info->is_running = false;

			rotation_keyhandler(event, main_info, true);
			scaling_keyhandler(event, main_info, true);
			translate_handler(event, main_info, true);
			break;
		case SDL_KEYUP:
			rotation_keyhandler(event, main_info, false);
			scaling_keyhandler(event, main_info, false);
			translate_handler(event, main_info, false);
			break;
	}
	update_center(main_info);
	update_angle(main_info);
	update_scale(main_info);
}

void	render(t_main_info *main_info) {

	// temp
	SDL_SetRenderDrawColor(main_info->renderer, 0, 0, 0, 255);
	SDL_RenderClear(main_info->renderer);

	// draw a rectangle
	SDL_SetRenderDrawColor(main_info->renderer, 255, 0, 0, 255);
	int i = 0;
	int j = 0;

	while (i < main_info->map_y) {
		j = -1;
		while (++j < main_info->map_x) {
			t_vec4 NDC = orthographic(main_info, main_info->projectionMatrix, i, j);
			main_info->screen_post_calc[i][j].x = (int)((NDC.x + 1) * 0.5 * main_info->screen_width);
			main_info->screen_post_calc[i][j].y = (int)((1 - (NDC.y + 1) * 0.5) * main_info->screen_height);
		}
		i++;
	}
	i = 0;
	while (i + 1 < main_info->map_y) {
		j = 0;
		while (j + 1 < main_info->map_x) {
			SDL_RenderDrawLine(main_info->renderer, main_info->screen_post_calc[i][j].x, main_info->screen_post_calc[i][j].y, main_info->screen_post_calc[i][j + 1].x, main_info->screen_post_calc[i][j + 1].y);
			SDL_RenderDrawLine(main_info->renderer, main_info->screen_post_calc[i][j].x, main_info->screen_post_calc[i][j].y, main_info->screen_post_calc[i + 1][j].x, main_info->screen_post_calc[i + 1][j].y);
			if (i + 2 == main_info->map_y) {
				SDL_RenderDrawLine(main_info->renderer, main_info->screen_post_calc[i + 1][j].x, main_info->screen_post_calc[i + 1][j].y, main_info->screen_post_calc[i + 1][j + 1].x, main_info->screen_post_calc[i + 1][j + 1].y);
			}
			if (j + 2 == main_info->map_x) {
				SDL_RenderDrawLine(main_info->renderer, main_info->screen_post_calc[i][j + 1].x, main_info->screen_post_calc[i][j + 1].y, main_info->screen_post_calc[i + 1][j + 1].x, main_info->screen_post_calc[i + 1][j + 1].y);
			}
			j++;
		}
		i++;
	}
	SDL_RenderPresent(main_info->renderer);
}

void	update(t_main_info *main_info) {
	update_xMatrix(main_info->xRotationMatrix, main_info->xAngle);
	update_yMatrix(main_info->yRotationMatrix, main_info->yAngle);
	update_zMatrix(main_info->zRotationMatrix, main_info->zAngle);

	float	tmp[4][4];
	multiplyMatrix(main_info->xRotationMatrix, main_info->yRotationMatrix, main_info->rotationMatrix);
	multiplyMatrix(main_info->rotationMatrix, main_info->zRotationMatrix, tmp);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			main_info->rotationMatrix[i][j] = tmp[i][j];
			tmp[i][j] = 0.0f;
		}
	}

	update_translate(main_info);
	update_scaleMatrix(main_info->scalingMatrix, main_info->scale);
}

int main(int argc, char **argv) {
	t_main_info	main_info;

	(void)argc;
	if (setup(argv, &main_info)) {
		return (1);
	}

	
	while (main_info.is_running) {
		process_input(&main_info);
		update(&main_info);
		render(&main_info);
	}

	cleanup(&main_info);
	return (0);
}

// NOTES
// smt wrong with ndc conversion