/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/02/12 19:50:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**get_file_contents(char *file)
{
	int		fd;
	int		ret;
	char	*file_contents;
	char	**file_lines;
	char 	*map_start;
	
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
	file_contents = malloc(sizeof(char) * ret);
	ret = read(fd, file_contents, ret);
	if (ret == -1)
		return (NULL);
	close(fd);
	file_lines = ft_split(file_contents, '\n');
	if (!file_lines)
		return (ft_split_free(file_lines), NULL);
	ft_print_split(file_lines);
	if (ft_split_count(file_lines) < 9)
		return (ft_split_free(file_lines), NULL);
	map_start = ft_strnstr(file_contents, file_lines[6], ft_strlen(file_contents));
	if (!map_start)
		return (ft_split_free(file_lines), NULL);
	printf("\n");
	write(1, map_start, ft_strlen(map_start));
	// CHECK here if map has empty lines
	free(file_contents);
	return (file_lines);
}

t_start	*parser(int argc, char **argv)
{
	t_start	*start;
	char	**file_lines;

	if (argc != 2)
		return (NULL);
	if (check_file_extension(argv[1]) == EXIT_FAILURE)
		return (NULL);
	file_lines = get_file_contents(argv[1]);
	if (!file_lines)
		return (NULL);
	start = malloc(sizeof(t_start));
	if (!start)
		return (ft_split_free(file_lines), NULL);
	return (start);
}
