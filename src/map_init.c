/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:57:49 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/19 15:57:49 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_lines_check(char *s) {
	int i = 0;
	
	while (s[i]) {
		if (!(s[i] >= '0' && s[i] <= '9') && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && !(s[i] == '-' && (s[i + 1] >= '0' && s[i + 1] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

int white_space_check(char *s) {
	int i = 0;
	
	while (s[i]) {
		if (!((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			return (1);
		i++;
	}
	return (0);
}

int arr2d_len(char **s) {
	int i = 0;
	while (s[i]) {
		i++;
	}
	return (i);
}

int	getting_file_content(t_file_lst **full_lst, int fd) {
	char		*buffer;
	t_file_lst	*new_node;
	
	buffer = get_next_line(fd);
	while (buffer) {
		new_node = create_filenode(buffer);
		if (!new_node) {
			ft_file_lstclear(full_lst, free);
			close(fd);
			printf("ERROR: Failed to create File_lst Node\n");
			return (1);
		}
		ft_file_lstadd_back(full_lst, new_node);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	getting_map(t_file_lst **full_lst, int *map_start, int *map_end, int *i) {
	t_file_lst	*tmp = *full_lst;
	int			map_checkres = 0;

	while (tmp)  {
		map_checkres = map_lines_check(tmp->s);
		if (map_checkres == 1 && *map_end == 0) {
			*map_end = *i;
			break;
		}
		tmp = tmp->next;
		(*i)++;
		// printf("%s", tmp->s);
		// printf("res: %d\n", map_checkres);
	}

	// TODO:
	while (tmp) {
		if (white_space_check(tmp->s))
			break;
		(*map_end)--;
		tmp = tmp->prev;
	}
	t_file_lst	*tmp = *full_lst;
	while (tmp) {
		if (white_space_check(tmp->s))
			break;
		(*map_start)++;
		tmp = tmp->next;
	}
}

void	freeing_arr2d(char **arr, int len) {
	int i = 0;

	while (i < len) {
		free(arr[i++]);
	}
	free(arr);
}

int all_digits(char **arr) {
	int i = 1;
	int j = 0;
	while (arr[i]) {
		j = 0;
		while (arr[i][j]) {
			if (!(arr[i][j] >= '0' && arr[i][j] <= '9') && arr[i][j] != '\n' && !((arr[i][j] >= 9 && arr[i][j] <= 13) || arr[i][j] == 32)) {
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	getting_map_info_util(char *s, unsigned int *val, int *counter) {
	char	**HighLowCheck;
	int		HighLowLen = 0;

	HighLowCheck = ft_split(s, ' ');
	if (!HighLowCheck) {
		printf("ERROR: Malloc failed\n");
		return (1);
	}
	HighLowLen = arr2d_len(HighLowCheck);
	if (HighLowLen != 5 || all_digits(HighLowCheck)) {
		freeing_arr2d(HighLowCheck, HighLowLen);
		printf("ERROR: Improper format for HIGH variable\n");
		return (1);
	}

	int		n1 = atoi(HighLowCheck[1]);
	int		n2 = atoi(HighLowCheck[2]);
	int		n3 = atoi(HighLowCheck[3]);
	int		n4 = atoi(HighLowCheck[4]);
	freeing_arr2d(HighLowCheck, HighLowLen);
	if (n1 > 256 || n2 > 256 || n3 > 256 || n4 > 256) {
		printf("ERROR: Value exceeding 256");
		return (1);
	}
	*val += (n1 << 24) + (n2 << 16) + (n3 << 8) + n4;
	(*counter)++;
	return (0);
}

int	getting_map_info(t_file_lst *full_lst, int i, unsigned int *HighVal, unsigned int *LowVal) {
	t_file_lst *tmp = full_lst;
	int j = -1;

	// getting to where getting_map left off
	while (++j < i)
		tmp = tmp->next;

	int	strcmpHigh;
	int strcmpLow;
	int	HighLowCounter[2];
	HighLowCounter[0] = 0;
	HighLowCounter[1] = 0;
	while (tmp) {
		strcmpHigh = ft_strncmp(tmp->s, "HIGH:", 4);
		strcmpLow = ft_strncmp(tmp->s, "LOW:", 3);
		if (strcmpHigh && strcmpLow && white_space_check(tmp->s)) {
			printf("ERROR: Invalid character found\n");
			return (1);
		}
		else if (strcmpHigh == 0) {
			if (getting_map_info_util(tmp->s, HighVal, &HighLowCounter[0]))
				return (1);
		}
		else if (strcmpLow == 0) {
			if (getting_map_info_util(tmp->s, LowVal, &HighLowCounter[1]))
				return (1);
		}
		tmp = tmp->next;
	}
	if (HighLowCounter[0] != 1 && HighLowCounter[1] != 1) {
		printf("ERROR: Incorrect amount of HIGH or LOW arguments\n");
		return (1);
	}
	return (0);
}

int	validate_input(char **argv, t_main_info *main_info) {
	t_file_lst	*full_lst = NULL;
	int			fd;

	// checking file format
	printf("%s\n", argv[1]);
	if (!argv[1]) {
		printf("ERROR: Incorrect amount of args\n");
		return (1);
	}
	printf("Passed: Args check\n");
	int	first_stringLen = ft_strlen(argv[1]) - 1;
	if (!(argv[1][first_stringLen--] == 'f' && argv[1][first_stringLen--] == 'd' && argv[1][first_stringLen] == 'f')) {
		printf("ERROR: Incorrect file format\n");
		return (1);
	}
	printf("Passed: .fdf check\n");

	// checking file existing
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		printf("ERROR: Out file failed to open\n");
		return (1);
	}
	printf("Passed: File check\n");

	// getting file content
	if (getting_file_content(&full_lst, fd))
		return (1);
	printf("Passed: Getting file content\n");

	int map_start = 0;
	int map_end = 0;
	int i = 0;
	getting_map(&full_lst, &map_start, &map_end, &i);

	unsigned int HighVal = 0;
	unsigned int LowVal = 0;
	if (getting_map_info(full_lst, i, &HighVal, &LowVal)) {
		ft_file_lstclear(&full_lst, free);
		return (1);
	}
	printf("Passed: Getting map info\n");
	
	

	printf("map start: %d | map end: %d | Highval: %x | LowVal: %x\n", map_start, map_end, HighVal, LowVal);
	return (0);
}

int main(int argc, char **argv) {
	t_main_info main_info;
	if (validate_input(argv, &main_info)) {
		printf("it failed a check\n");
		return (1);
	}
	return (0);
}
// NOTE LEFT OFF NEEDING TO DO MAP CONVERSION TO 2D ARRAY
// NEED TO FIND MAP X AND Y