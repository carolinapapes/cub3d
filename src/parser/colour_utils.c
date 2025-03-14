/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:33:42 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/14 18:24:27 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	skip_spaces_and_plus(char *line, int *i)
{
	int	plus_seen;

	plus_seen = 0;
	while (line[*i] == ' ' || line[*i] == '+')
	{
		if (line[*i] == '+')
		{
			if (plus_seen)
				return (1);
			plus_seen = 1;
		}
		(*i)++;
	}
	return (0);
}

int	validate_comma(char *line, int *i)
{
	if (line[*i] != ',')
		return (1);
	(*i)++;
	if (line[*i] != ' ')
		return (1);
	while (line[*i] == ' ')
		(*i)++;
	return (0);
}

int	get_next_value(char *line, int *i, unsigned char *pigment)
{
	int	start;

	if (skip_spaces_and_plus(line, i))
		return (1);
	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (*i == start || check_pigment(line + start, *i - start, pigment))
		return (1);
	while (line[*i] == ' ')
		(*i)++;
	return (validate_comma(line, i));
}

int	extract_last_value(char *line, int *index, unsigned char *pigment)
{
	int	start;
	int	plus_seen;

	plus_seen = 0;
	while (line[*index] == ' ')
		(*index)++;
	while (line[*index] == '+')
	{
		if (plus_seen)
			return (1);
		plus_seen = 1;
		(*index)++;
		while (line[*index] == ' ')
			(*index)++;
	}
	start = *index;
	while (line[*index] && ft_isdigit(line[*index]))
		(*index)++;
	if (*index == start || check_pigment(line + start, *index - start, pigment))
	{
		return (1);
	}
	while (line[*index] == ' ')
		(*index)++;
	if (line[*index] != '\0')
		return (1);
	return (0);
}
