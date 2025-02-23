/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:04:48 by kate              #+#    #+#             */
/*   Updated: 2025/02/23 01:11:20 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//all functions to read the file and check
#include "cube3d.h"

int	check_file_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_line_length(int fd)
{
	int		length;
	char	line[1];
	int		res;

	length = -1;
	res = 1;
	while (res != -1 && res != 0)
	{
		res = read(fd, line, 1);
		length++;
	}
	return (length);
}

char	*read_file(char *file)
{
	int		fd;
	int		ret;
	char	*file_contents;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = get_line_length(fd);
	close(fd);
	if (ret == 0)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file_contents = malloc(sizeof(char) * (ret + 1));
	ret = read(fd, file_contents, ret);
	file_contents[ret] = '\0';
	if (ret == -1)
		return (NULL);
	close(fd);
	return (file_contents);
	
}
