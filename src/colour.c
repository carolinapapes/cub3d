/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/25 18:52:03 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
/*
	1. Function that SEARCH FOR C or F
	2. Function that check is there is something else beside the letter
	3. checks if the color is possible
	4. saves the color to the struct
*/

int	is_letter(char *line, char *c)
{
	if (!line || !c)
		return (1);
	while(*line)
		line++;
	if (*line == '\0' || *line != c)
		return (1);
	//function to check if enough material for color
	//function to unite numbers for a colour
	
}

int	check_line_for_colour(char **elements)
{
	int	line;

	line = 0;
	while (elements[line] != NULL)
	{
		if (is_letter(elements[line], "C") == 0)
		if 
			return (1);
		line++;
	}
}

check_for_color(char **elements)
{
	if (check_line_for_color(elements) == 1)
	{
		return (1);
	}
	return (0);
}