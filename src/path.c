/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:01:54 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/11 02:39:31 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

/*int	check_dir(char **elements, char *dir_name, char **future_path)
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
}*/

int	check_dir(char *path, char **future_path)
{
	if (*future_path != NULL) // quiere decir que dir se ha repetido
		return (1);
	if (is_path_valid(path) == 1)
		return (1);
	*future_path = save_path(path);
	
	return (0);
}

int	is_texture(char *line, t_start *start)
{
	char	**texture;
	int		res;

	res = 0;
	texture = ft_split(line, ' ');
	if (!texture)
		return (1);
	if (texture[0] == NULL || texture[1] == NULL || texture[2] != NULL)
		return (0);
	else if (ft_strncmp(texture[0], "NO", ft_strlen("NO") ) == 0)
		res = check_dir(texture[1], &(start->n_fd));
	else if (ft_strncmp(texture[0], "SO", ft_strlen("SO")) == 0)
		res = check_dir(texture[1], &(start->s_fd));
	else if (ft_strncmp(texture[0], "WE", ft_strlen("WE") ) == 0)
		res = check_dir(texture[1], &(start->w_fd));
	else if (ft_strncmp(texture[0], "EA", ft_strlen("EA") ) == 0)
		res = check_dir(texture[1], &(start->e_fd));
	free_char_array(&texture);
	return (res);
}

/*int	check_four_dir(t_start *start, char **elements)
{
	if (check_dir(elements, "NO ", &(start->n_fd)) == 1 || check_dir(elements, "SO ", &(start->s_fd)) == 1 || \
		check_dir(elements, "WE ", &(start->w_fd)) == 1 || check_dir(elements, "EA ", &(start->e_fd)) == 1)
	{
		//write a function for it
		free_line(&start->n_fd);
		free_line(&start->s_fd);
		free_line(&start->w_fd);
		free_line(&start->e_fd);
		return (1);
	}
	printf("Valid texture path for %s: \n", start->n_fd);
	printf("Valid texture path for %s: \n", start->w_fd);
	printf("Valid texture path for %s: \n", start->e_fd);
	printf("Valid texture path for %s: \n", start->s_fd);
	return (0);
}*/
