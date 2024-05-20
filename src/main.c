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

// int	freeing_2darr(char **content, int len) {
// 	int i = 0;
// 	while (i < len)
// 		free(content[i++]);
// 	free(content);
// 	return (1);
// }

// int	skip_whitespace(char **content, int arr_len, int increment, int start_pos) {
// 	int i = 0;

// 	if (arr_len == 0 || !content || !*content)
// 		return (-1);
	
// 	while (start_pos >= 0 && content[start_pos]) {
// 		i = -1;
// 		while (content[start_pos][++i]) {
// 			if (content[start_pos][i] != ' ' && content[start_pos][i] != '\n')
// 				return (start_pos);
// 		}
// 		start_pos++;
// 	}
// 	return (-1);
// }

// need 2 checkers
//	one for checking if all positions are numbers and not alphabets
//	one for checking the rest of the HIGH LOW maybe adding MIDDLE in the future

int	validate_input(char **argv, t_main_info *main_info) {
	// checking file format
	if (!argv[1])
		return (1);
	int	first_stringLen = ft_strlen(argv[1]);
	if (!(argv[1][first_stringLen--] == 'f' && argv[1][first_stringLen--] == 'd' && argv[1][first_stringLen] == 'f'))
		return (1);

	// checking file existing
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);

	// getting file content
	int fd;
	char *buffer;
	t_file_lst *full_list = NULL;
	t_file_lst *new_node;
	
	fd = open("out", O_RDONLY);
	if (fd < 0) {
		printf("Error out file failed to open\n");
		return (1);
	}
	
	buffer = get_next_line(fd);
	while (buffer) {
		new_node = create_filenode(buffer);
		if (!new_node) {
			// do error handling
		}
			
		ft_file_lstadd_back(&full_list, new_node);
		
		// tmp = fullstring;
		// fullstring = ft_strjoin(fullstring, buffer);
		// free(tmp);
		
		buffer = get_next_line(fd);
	}

	t_file_lst	*tmp = full_list;
	while (tmp)  {
		printf("%s\n", tmp->s);
		tmp = tmp->next;
	}

	// close(fd);
	// char	**content = ft_split(file_content, '\n');
	// if (!content) {
	// 	free(file_content);
	// 	return (1);
	// }
	
	// int map_start_index = skip_whitespace(content, arr_len, 1, 0);
	// int map_end_index;
	// int map_info_start_index;
	// int map_info_end_index;
	


	return (0);
}

// TODO: fix this for proper input file
int	validate_input(char **argv, t_main_info *main_info) {
	// hardcoded currently 
	(void)argv;
	main_info->map = ft_split("11111\n10001\n10001\n10001\n11111", '\n');
	main_info->map_x = 5;
	main_info->map_y = 5;

	// printing map
	printf("Current map:\n");
	for (int i = 0; i < main_info->map_y; i++) {
		for (int j = 0; j < main_info->map_x; j++)
			printf("%c ", main_info->map[i][j]);
		printf("\n");
	}

	return (0);
}

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
		printf("Error: code %d\n", main_info.error_code);
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