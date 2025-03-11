/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/11 16:56:41 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	1. control big numbers
	2. 
*/

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

int extract_color(char *pigment)
{
	int color;
	int	i;

	i = 0;
	if (pigment[0] == '\0')
		return (-1);
	while(pigment[i] != '\0')
	{
		if (ft_isdigit(pigment[i]) == 0)
		{
			printf("simbolos no numericos en el pigmento\n");
			return (-1);
		}
		i++;
	}
	color = ft_atoi(pigment);
	return (color);
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

//gestionar numero grandes
int	check_line_for_color(char **palet, t_color *color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (palet[i] != NULL)
	{
		printf("contenido: |%s|num: %d\n", palet[i], i);
		i++;
	}
	if (i != 4 )
		return (1);
	printf("he sobrevivido\n");
	r = extract_color(palet[1]);
	g = extract_color(palet[2]);
	b = extract_color(palet[3]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	(*color).r = r;
	(*color).g = g;
	(*color).b = b;
	(*color).rgba = (color->r << 24) | (color->g << 16) | (color->b<< 8) | 255;
	return (0);
}
void remove_commas(char **palet)
{
    int i;
    int len;

    i = 0;
    while (palet[i] != NULL)
    {
        len = ft_strlen(palet[i]); // Get string length
        if (len > 0 && palet[i][len - 1] == ',') // If last char is ','
            palet[i][len - 1] = '\0'; // Replace with null terminator
        i++;
    }
}
char *remove_trailing_comma(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len > 0 && str[len - 1] == ',')
        return ft_substr(str, 0, len - 1); // Create new string without comma
    return ft_strdup(str);
}

void fix_palet(char **palet)
{
    int i;
    char *temp;

    i = 0;
    while (palet[i])
    {
        temp = remove_trailing_comma(palet[i]);
        free(palet[i]);  // Free old string
        palet[i] = temp; // Assign new string
        i++;
    }
}

int	is_color(char *line, t_start *start)
{
	char	**palet;
	int		res;
	int		i;

	res = 0;
	i = 0;
	palet  = ft_split(line, ' ');
	while(palet[i] != NULL)
	{
		printf("%s\n", palet[i]);
		i++;
	}
	fix_palet(palet);
	i = 0;
	while(palet[i] != NULL)
	{
		printf("|%s|\n", palet[i]);
		i++;
	}
	if (ft_strncmp(palet[0], "F", 1) == 0)
	{
		printf("he entrado en floor color check\n");
		res = check_line_for_color(palet, &(*start).floor);
	}
	else if (ft_strncmp(palet[0], "C", 1) == 0)
		res = check_line_for_color(palet, &(*start).ceiling);
	free_char_array(&palet);
	printf("ceiling colours r: %d, b: %d, g: %d  color total es: %d\n", start->ceiling.r, start->ceiling.b, start->ceiling.g, start->ceiling.rgba);
	printf("floor colours r: %d, b: %d, g: %d color total es: %d\n", start->floor.r, start->floor.b, start->floor.g, start->floor.rgba);
	return (res);
}
/*
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

*/