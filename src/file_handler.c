/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:04:48 by kate              #+#    #+#             */
/*   Updated: 2025/03/10 19:56:49 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//all functions to read the file and check
#include "cube3d.h"

int	check_file_extension(char *file, char *extension_name)
{
	int		extension_len;
	char	*extension;
	

	if (!file || !extension_name)
		return (EXIT_FAILURE);
	extension_len = ft_strlen(extension_name);
	extension = ft_strrchr(file, '.');
	
	if (!extension || ft_strncmp(extension, extension_name, extension_len))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_line_length(int fd)
{
	int		length;
	char	line[1];
	int		res;

	length = 0;
	while ((res = read(fd, line, 1)) > 0)
		length++;
	if (res == -1)
		return (-1);
	return (length);
}

int	read_file(char *file, char **line)
{
	int		fd;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	len = get_line_length(fd);
	close(fd);
	if (len <= 0)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	*line = malloc(len + 1);
	if (!(*line))
		return (1);
	int read_bytes = read(fd, *line, len);
	close(fd);
	if (read_bytes == -1)
	{
		free(*line);
		return (1);
	}
	(*line)[read_bytes] = '\0';
	return (0);
}




char	*extract_content(char *file)
{
	char *line;

	line = NULL;
	if (check_file_extension(file, ".cub") == EXIT_FAILURE)
		return (NULL);
	if	(is_path_valid(file) == EXIT_FAILURE)
		return (NULL);
	read_file(file, &line);
	return (line);
}
