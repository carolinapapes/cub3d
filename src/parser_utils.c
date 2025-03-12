/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:27:42 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/12 16:40:36 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_ispace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	empty_string(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (1);
		line++;
	}
	return (0);
}

int	ft_split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	handle_newlines(const char *s, int *i)
{
	int	newlines_in_a_row;

	newlines_in_a_row = 0;
	while (s[*i] != '\0' && (s[*i] == '\n' || ft_ispace(s[*i])))
	{
		if (s[*i] == '\n')
			newlines_in_a_row++;
		(*i)++;
	}
	return (newlines_in_a_row);
}

int	count_lines(const char *s)
{
	int	i;
	int	lines;
	int	newlines_in_a_row;

	i = 0;
	lines = 0;
	newlines_in_a_row = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			lines++;
			i++;
			newlines_in_a_row = handle_newlines(s, &i);
			if (newlines_in_a_row > 1)
				lines++;
		}
		else
			i++;
	}
	return (lines);
}
