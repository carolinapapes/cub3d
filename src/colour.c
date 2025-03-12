/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/12 01:39:06 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	1. control big numbers
	2. coma
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
		i++;
	if (i != 4 )
		return (1);
	r = extract_color(palet[1]);
	g = extract_color(palet[2]);
	b = extract_color(palet[3]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	color->r = r;
	color->g = g;
	color->b = b;
	color->repeated = 0;
	color->rgba = (r << 24) | (g << 16) | (b<< 8) | 255;
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

	res = 1;
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
	if (ft_strncmp(palet[0], "F", 1) == 0 && start->floor.repeated == -1)
	{
		printf("he entrado en floor color check %s\n", palet[0]);
		res = check_line_for_color(palet, &(start->floor));
	}
	else if (ft_strncmp(palet[0], "C", 1) == 0 && start->ceiling.repeated == -1)
	{
		printf("he entrado en ceiling color check %s\n", palet[0]);
		res = check_line_for_color(palet, &(*start).ceiling);
	}
	printf("res es %d\n", res);
	free_char_array(&palet);
	return (res);
}
