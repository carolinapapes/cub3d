/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:15 by capapes           #+#    #+#             */
/*   Updated: 2025/02/19 17:08:33 by kkoval           ###   ########.fr       */
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

char	*get_file_contents(char *file)
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

char	**check_file_contents(char *line)
{
	char	**file_lines;
	char	*map_start;

	if (check_map(line) == 1)
	{
		printf("Error in the map\n"); //TODO delete later
		return(NULL);
	}
	file_lines = ft_split(line, '\n');
	if (!file_lines)
		return (ft_split_free(file_lines), NULL);
	ft_print_split(file_lines); // TODO delete later
	if (ft_split_count(file_lines) < 9)
		return (ft_split_free(file_lines), NULL);
	//find map start and check for empty lines
		//return (ft_split_free(file_lines), NULL);
	printf("\n");
	//write(1, map_start, ft_strlen(map_start));
	
	return (file_lines);
}

t_start	*parser_controler(int argc, char **argv)
{
	t_start	*start;
	char	*line;
	char	**file_lines;

	if (argc != 2)
		return (NULL);
	if (check_file_extension(argv[1]) == EXIT_FAILURE)
		return (NULL);
	line = get_file_contents(argv[1]);
	if (line == NULL)
		return (NULL);
	file_lines = check_file_contents(line);
	if (!file_lines)
	{
		free(line);
		return (NULL);
	}
	start = malloc(sizeof(t_start));
	if (!start)
		return (ft_split_free(file_lines), NULL);
	//mre serious check for path and closed map
	return (start);
}
