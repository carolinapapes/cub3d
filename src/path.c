/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:01:54 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/11 17:01:01 by kkoval           ###   ########.fr       */
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

int	check_dir(char *path, char **future_path)
{
	if (*future_path != NULL)
		return (-1);
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
	{
		free_char_array(&texture);
		return (1);
	}
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
