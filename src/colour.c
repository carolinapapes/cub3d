/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/27 03:15:48 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
/*
	1. Function that SEARCH FOR C or F
	2. Function that check is there is something else beside the letter
	3. checks if the color is possible
	4. saves the color to the struct
*/


int	convert_colour()

int	is_letter(char *line, char *c, int *colour)
{
	if (!line || !c)
		return (-1);
	while (*line)
		line++;
	if (*line == '\0' || *line != c)
		return (-1);
	if (ft_strncmp(line, c, ft_strlen(c)) != 0)
		return (1);
	line++;
	

	//function to check if enough material for color
	//function to unite numbers for a colour
	return (0);
}

int	check_line_for_colour(t_start *start, char **elements)
{
	int	i;
	int	c_count;
	int	f_count;

	i = 0;
	c_count = 0;
	f_count = 0;
	while (elements[i] != NULL)
	{
		if (is_letter(elements[i], "C", &(start->ceiling)) == 0)
			c_count++;
		else if (is_letter(elements[i], "F", &(start->floor)) == 0)
			f_count++;
		i++;
	}
	if (c_count != 1 || f_count != 1)
		return (1);
	return (0);
}

check_for_color(t_start *start, char **elements)
{
	if (check_line_for_color(start, elements) == 1)
	{
		printf("no hay colorsitos para el suelo o para el cielo :(\n)");
		return (1);
	}
	return (0);
}