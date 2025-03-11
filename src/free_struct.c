/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:39:47 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/11 18:46:10 by kkoval           ###   ########.fr       */
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
	return ;
}

// free the whole struct start in case of error or exit
void	free_start(t_start *start)
{
	if (!start)
		return ;
	if (start->map.map_int != NULL)
		free_int_array(&start->map.map_int, start->map.size_int.y);
	if (start->n_fd != NULL)
		free_line(&start->n_fd);
	if (start->s_fd != NULL)
		free_line(&start->s_fd);
	if (start->w_fd != NULL)
		free_line(&start->w_fd);
	if (start->e_fd != NULL)
		free_line(&start->e_fd);
	return ;
}
