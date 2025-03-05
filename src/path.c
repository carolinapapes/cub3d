/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:01:54 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/05 16:58:30 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    1.detectar los 4 paths
    2. mirar que tengan una extension correcta
    3. mirar que se puedan abrir
    4. guardar la direccion en la esctrucura
	5. checkear si es un directio chekear si es.png
*/
#include "cube3d.h"
#include <sys/stat.h>

char	*save_path(char *path)
{
	char	*p;
	int		len;
	int		i;

	len = ft_strlen(path);
	i = 0;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = path[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

int	is_path_valid(char *path)
{
    int	dir;
	int	fd;

	dir = open(path, O_DIRECTORY);
	if (dir == -1)
	{
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close (fd);
			return (0);
		}
		return (1);
	}
	close(dir);
	return (1);
}

int	is_dir(char **future_path, char *line, char *dir_name)
{
	if (!line || !dir_name)
		return (1);
	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	if (ft_strncmp(line, dir_name, ft_strlen(dir_name)) != 0)
		return (1);
	printf("hay dir en line\n");
	line += strlen(dir_name);
	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
	{
		return (1);
	}
	if (is_path_valid(line) == 1)
		return (1);
	if (check_file_extension(line, ".png") == 1)
		return (1);
	*future_path = save_path(line);
	if (*future_path == NULL)
		return (1);
	printf("Valid texture path for %s: %s\n", dir_name, line);
	return (0);
}

int	check_dir(char **elements, char *dir_name, char **future_path)
{
	int	line;
	int	found_count;

	line = 0;
	found_count = 0;
	while (elements[line] != NULL)
	{
		if (is_dir(future_path, elements[line], dir_name) == 0)
			found_count++;
		line++;
	}
	if (found_count != 1)
		return (1);
	return (0);
}

int	check_four_dir(t_start *start, char **elements)
{
	start->n_fd = NULL; // TODO initiate in the start
	start->s_fd = NULL;
	start->w_fd = NULL;
	start->e_fd = NULL;
	if (check_dir(elements, "NO ", &start->n_fd) == 1 || check_dir(elements, "SO ", &start->s_fd) == 1 || \
		check_dir(elements, "WE ", &start->w_fd) == 1 || check_dir(elements, "EA ", &start->e_fd) == 1)
	{
		//write a function for it
		free_line(&start->n_fd);
		free_line(&start->s_fd);
		free_line(&start->w_fd);
		free_line(&start->e_fd);
		return (1);
	}
	return (0);
}
