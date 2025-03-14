/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/14 15:17:48 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	extract_pigment(char *pigment, unsigned char *chosen_pigment)
{
	int	num;

	num = ft_atoi(pigment);
	if (num >= 0 && num <= 255)
	{
		*chosen_pigment = (unsigned char)num;
		return (0);
	}
	return (1);
}

int	get_number_length(char *line, int *i, int line_len)
{
	int	num_len;

	num_len = 0;
	while (*i < line_len && ft_isdigit(line[*i]))
	{
		(*i)++;
		num_len++;
	}
	return (num_len);
}

int	check_pigment(char *line, int line_len, unsigned char *pigment)
{
	int		i;
	int		num_len;
	char	*new_pigment;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '-' || line[i] == '\0')
		return (1);
	if (line[i] == '+')
		i++;
	num_len = get_number_length(line, &i, line_len);
	if (num_len == 0 || num_len > 3)
		return (1);
	new_pigment = ft_substr(line, i - num_len, num_len);
	if (!new_pigment)
		return (1);
	if (extract_pigment(new_pigment, pigment))
	{
		free(new_pigment);
		return (1);
	}
	free(new_pigment);
	return (0);
}

int	color_extract(char *line, t_color *color)
{
	int	i;

	i = 0;
	line++;
	if (*line != ' ' || !*line)
		return (1);
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (1);
	if (get_next_value(line, &i, &color->r, 1) || \
		get_next_value(line, &i, &color->g, 1) || \
		extract_last_value(line, &i, &color->b))
		return (1);
	color->a = 255;
	color->rgba = (color->r << 24) | (color->g << 16) \
	| (color->b << 8) | color->a;
	return (0);
}

int	is_color(char *line, t_start *start)
{
	int	res;

	res = 1;
	while (*line && *line == ' ')
		line++;
	if (ft_strncmp(line, "F", 1) == 0 && start->f_repeated == -1)
	{
		res = color_extract(line, &(start->floor));
		start->f_repeated++;
	}
	else if (ft_strncmp(line, "C", 1) == 0 && start->c_repeated == -1)
	{
		res = color_extract(line, &(start->ceiling));
		start->c_repeated++;
	}
	return (res);
}
