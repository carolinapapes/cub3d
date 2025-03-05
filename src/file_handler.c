/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:04:48 by kate              #+#    #+#             */
/*   Updated: 2025/03/05 16:18:43 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//all functions to read the file and check
#include "cube3d.h"

int	check_file_extension(char *file, char *exten_name)
{
	char	*extension;
	int		exten_len;

	if (!file || !exten_name)
		return (EXIT_FAILURE);
	extension = ft_strrchr(file, '.');
	exten_len = ft_strlen(exten_name);
	if (!extension || ft_strncmp(extension, ".cub", 5))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_line_length(int fd)
{
	int		length;
	char	line[1];
	int		res;

	length = 0;  // Fix: Start from 0
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
	if (len <= 0)  // Fix: Handle errors and empty files correctly
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	*line = malloc(len + 1);
	if (!(*line))  // Fix: Check malloc success
		return (1);
	int read_bytes = read(fd, *line, len);
	close(fd);
	if (read_bytes == -1)  // Fix: Check read() return value
	{
		free(*line);
		return (1);
	}
	(*line)[read_bytes] = '\0';  // Fix: Only write null terminator if read() succeeds
	return (0);
}
