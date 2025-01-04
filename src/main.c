/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 04:25:03 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 06:20:51 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tree.h"
#include <dirent.h>

void	args_stepper(int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
}

void print_tree(char *child, int depth, int is_dir, int is_last) {
	char *last_dir = ft_strrchr(child, '/');
	char *prefix = is_last ? "└── " : "├── ";
	char *color = is_dir ? RED : GRAY;

	for (int j = 0; j < depth; j++) {
		ft_color_printf(GRAY, j == 0 ? "     " : "│    ");
	}
	ft_color_printf(color, "%s%s\n", prefix, last_dir ? last_dir + 1 : child);
}

void	ls_recurse(char *dir_path, int depth_level)
{
	DIR *d;
	struct dirent *dir;
	char	path[PATH_MAX];

	d = opendir(dir_path);
	if (!d)
		return ;
	dir = readdir(d);
	while (dir != NULL) {
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".git") == 0)
		{
			dir = readdir(d);
			continue ;
		}
		if (dir->d_type == DT_DIR) {
			strcpy(path, dir_path);
			strcat(path, "/");
			strcat(path, dir->d_name);
			print_tree(path, depth_level, 1, 1);
			ls_recurse(path, depth_level + 1);
			dir = readdir(d);
		}
		else
		{
			struct dirent *temp;
			if ((temp = readdir(d)) == NULL)
				print_tree(dir->d_name, depth_level, 0, 1);
			else
				print_tree(dir->d_name, depth_level, 0, 0);
			dir = temp;
		}
	}
	closedir(d);
}

void print_usage() {
	ft_printf("\n");
	ft_color_printf(RED, "Usage: ./tree [Directory Path]\n");
	ft_color_printf(RED, "│\n");
	ft_color_printf(RED, "└──");
	ft_color_printf(BLUE, "Example: ./tree .\n");
	ft_color_printf(RED, "│\n");
	ft_color_printf(RED, "└──");
	ft_color_printf(BLUE, "Example: ./tree /home/user\n");
	ft_printf("\n");
}

int	main(int argc, char **argv)
{
	args_stepper(&argc, &argv);

	if (argc == 1) {
		ft_color_printf(RED, "%s\n", argv[0]);
		ls_recurse(*argv, 1);
	}
	else
		print_usage();
	return (0);
}
