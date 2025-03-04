/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:39:47 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/28 01:49:17 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*free_line(char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

void	free_int_array(int ***array, int size_y)
{
	int	y;

	y = 0;
	if (!array || !*array)
		return ;
	while (y < size_y)
	{
		free((*array)[y]);
		y++;
	}
	free(*array);
	*array = NULL;
	printf("he entrado al free int\n");
	return ;
}

void	free_char_array(char ***split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
	printf("he entrado en free char\n");
	return ;
}

// free the whole struct start in case of error or exit
void	free_start(t_start *start)
{
	if (!start)
		return ;
	if (start->map.map_int != NULL)
		free_int_array(&start->map.map_int, start->map.size_int.y);
	printf("he estado en el free start\n");
	return ;
}
