/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/11 04:23:29 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int ft_atoi(const char *str)
{
	int res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int parse_color_component(char **line)
{
	int value;

	while (**line == ' ')
		(*line)++;
	if (**line < '0' || **line > '9')
		return (-1);
	value = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line == ' ')
		(*line)++;
	return (value);
}

int extract_color(t_color *color, char *line)
{
	int r;
	int	g;
	int	b;

	while (*line == ' ')
		line++;
	if (*line != 'F' && *line != 'C')
		return (1);
	line++;
	while (*line == ' ')
		line++;
	r = parse_color_component(&line);
	if (*line != ',')
		return (1);
	line++;
	g = parse_color_component(&line);
	if (*line != ',')
		return (1);
	line++;
	b = parse_color_component(&line);
	if (*line != '\0' && *line != ' ')
		return (1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	color->r = (unsigned char)r;
	color->g = (unsigned char)g;
	color->b = (unsigned char)b;
	color->a = 255;
	color->rgba = (color->r << 24) | (color->g << 16) | (color->b<< 8) | 255;
	return (0);
}

//int check_line_for_color(t_color *floor, t_color *ceiling, char *line)
{

	int f_count;
	int c_count;

	line = 0;
	f_count = 0;
	c_count = 0;
	while (line != NULL)
	{
		if (strstr(elements[line], "F") != NULL)
		{
			if (extract_color(floor, elements[line]) == 0)
				f_count++;
		}
		else if (strstr(elements[line], "C") != NULL)
		{
			if (extract_color(ceiling, elements[line]) == 0)
				c_count++;
		}
		line++;
	}
	if (c_count != 1|| f_count != 1)
		return (1);
	return (0);
}

int	check_for_color(t_start *start, char **elements)
{
	if (check_line_for_color(&(*start).floor, &(*start).ceiling, elements) == 1)
	{
		printf("no hay colorsitos para el suelo o para el cielo :(\n");
		return (1);
	}
	printf("ceiling colours r: %d, b: %d, g: %d  color total es: %d\n", start->ceiling.r, start->ceiling.b, start->ceiling.g, start->ceiling.rgba);
	printf("floor colours r: %d, b: %d, g: %d color total es: %d\n", start->floor.r, start->floor.b, start->floor.g, start->floor.rgba);
	return (0);
}
char *join_palet(char **palet)
{
    int     i;
    char    *result;
    char    *temp;

    if (!palet || !palet[0])
        return (NULL);
    result = ft_strdup(palet[0]);
    if (!result)
        return (NULL);
    i = 1;
    while (palet[i])
    {
        temp = ft_strjoin(result, " ");
        free(result);
        if (!temp)
            return (NULL);
        result = ft_strjoin(temp, palet[i]);
        free(temp);
        if (!result)
            return (NULL);
        i++;
    }
    return (result);
}

int	check_line_for_color(char **palette, t_start *start)
{

}

int	is_color(char *line, t_start *start)
{
	char	**palet_comas;
	char	**palet_n_comas;
	int		*new_line;
	int		res;

	palet = ft_split(line, ' ');
	if (!palet)
		return (1);
	new_line = join_palet(palet);
	if (!new_line)
		return (1);
	palet_n_comas = ft_split(new_line, ',');
	if (ft_strncmp(palet[0], 'F', 1) == 0)
		res = check_line_for_color(palet, start.floor);
	else if (ft_strncmp(palet[0], 'C', 1) == 0)
		res = check_line_for_color(palet, start.ceiling);
	free_char_array(&palet);
	printf("ceiling colours r: %d, b: %d, g: %d  color total es: %d\n", start->ceiling.r, start->ceiling.b, start->ceiling.g, start->ceiling.rgba);
	printf("floor colours r: %d, b: %d, g: %d color total es: %d\n", start->floor.r, start->floor.b, start->floor.g, start->floor.rgba);
	return (res);
}
