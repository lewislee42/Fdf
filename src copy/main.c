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

// // need 2 checkers
// //	one for checking if all positions are numbers and not alphabets
// //	one for checking the rest of the HIGH LOW maybe adding MIDDLE in the future

// int	validate_input(char **argv, t_main_info *main_info) {
// 	// checking file format
// 	if (!argv[1])
// 		return (1);
// 	int	first_stringLen = ft_strlen(argv[1]);
// 	if (!(argv[1][first_stringLen--] == 'f' && argv[1][first_stringLen--] == 'd' && argv[1][first_stringLen] == 'f'))
// 		return (1);

// 	// checking file existing
// 	int fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);

// 	// getting file content
// 	int		i = 0;
// 	char	*tmp;
// 	char	*file_content = "\0";
// 	char	*string = get_next_line(fd);
// 	int		arr_len = 1;
// 	if (!string) {
// 		close(fd);
// 		return (1);
// 	}
// 	while (string) {
// 		tmp = ft_strjoin(file_content, string);
// 		free(file_content);
// 		free(string);
// 		file_content = tmp;
// 		free(tmp);
// 		string = get_next_line(fd);
// 		arr_len++;
// 	}

// 	close(fd);
// 	char	**content = ft_split(file_content, '\n');
// 	if (!content) {
// 		free(file_content);
// 		return (1);
// 	}
	
// 	int map_start_index = skip_whitespace(content, arr_len, 1, 0);
// 	int map_end_index = ;
// 	int map_info_start_index;
// 	int map_info_end_index;
	


// 	return (0);
// }

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

// TODO: do error handling when malloc fails
void	init_pos(t_main_info *main_info) {
	int i = 0;
	int j = 0;
	main_info->points = malloc(sizeof(t_pos *) * (main_info->map_y + 1));
	while (i < main_info->map_y) {
		main_info->points[i] = malloc(sizeof(t_pos) * (main_info->map_x));
		j = 0;
		while (j < main_info->map_x) {
			main_info->points[i][j].x = j;
			main_info->points[i][j].y = i;
			main_info->points[i][j].z = 1;
			j++;
		}
		i++;
	}
	main_info->points[i] = NULL;
}

// TODO:
// 	need to add a freeing/cleanup function if the sdl_init fails
//	need to add a freeing/cleanup function if the window/renderer creation fails
int	setup(char **argv, t_main_info *main_info) {
	printf("Getting input file\n");
	if (validate_input(argv, main_info))
		return (1);

	init_pos(main_info);

	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return (1);
    }
	main_info->window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
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
			break;
	}
}

void	update() {

}

void	render(t_main_info *main_info) {

	// temp
	SDL_SetRenderDrawColor(main_info->renderer, 0, 0, 0, 255);
	SDL_RenderClear(main_info->renderer);

	// draw a rectangle
	// SDL_Rect rect = { 100, 100, 50, 50 };
	SDL_SetRenderDrawColor(main_info->renderer, 255, 0, 0, 255);
	int i = 0;
	int j = 0;
	while (i + 1 < main_info->map_y) {
		j = 0;
		while (j + 1 < main_info->map_x) {
			SDL_RenderDrawLine(main_info->renderer, main_info->points[i][j].x * 10, main_info->points[i][j].y * 10, main_info->points[i][j + 1].x * 10, main_info->points[i][j + 1].y * 10);
			SDL_RenderDrawLine(main_info->renderer, main_info->points[i][j].x * 10, main_info->points[i][j].y * 10, main_info->points[i + 1][j].x * 10, main_info->points[i + 1][j].y * 10);
			if (i + 1 == main_info->map_y) {
				SDL_RenderDrawLine(main_info->renderer, main_info->points[i][j + 1].x * 10, main_info->points[i][j + 1].y * 10, main_info->points[i + 1][j + 1].x * 10, main_info->points[i + 1][j + 1].y * 10);
			}
			j++;
		}
		i++;
	}

	SDL_RenderPresent(main_info->renderer);
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
		update();
		render(&main_info);
	}

	cleanup(&main_info);
	return (0);
}
