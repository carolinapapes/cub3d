/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/14 01:13:18 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int extract_pigment(char *pigment, unsigned char *chosen_pigment)
{
	int num;

	num = ft_atoi(pigment);
	if (num >= 0 && num <= 255)
	{
		*chosen_pigment = (unsigned char)num;
		return (0);
	}
	return (1);
}

int check_pigment(char *line, int line_len, unsigned char *pigment)
{
	int		i;
	int		num_len;
	char	*new_pigment;

	i = 0;
	num_len = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == '-' || line[i] == '\0')
		return (1);
	if (line[i] == '+')
		i++;
	while (i < line_len)
	{
		if (line[i] == ' ')
			break;
		if (ft_isdigit(line[i]) == 0)
			return (1);
		i++;
		num_len++;
	}
	if (num_len > 3)
		return (1);
	new_pigment = ft_substr(line, i - num_len, num_len);
	if (!new_pigment)
		return (1);
	if (extract_pigment(new_pigment, pigment) == 1)
	{
		free(new_pigment);
		return (1);
	}
	free(new_pigment);
	return (0);
}

int color_extract(char *line, t_color *color)
{
	int i;
	int start;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == '\0')
		return (1);
	if (check_pigment(line, i, &color->r) == 1)
		return (1);
	start = ++i;
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == '\0')
		return (1);
	if (check_pigment(line + start, i - start, &color->g) == 1)
		return (1);
	start = ++i;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	start = i;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			break;
		i++;
	}
	if (check_pigment(line+start, i - start, &color->b) == 1)
		return (1);
	while(line[i] != '\0')
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	color->a = 255;
	color->rgba = (color->r << 24) | (color->g << 16) | (color->b << 8) | 255;
	return (0);
}

int parse_color_line(char *line, t_color *color)
{
	printf("%c\n", *line);
	line++;
	if (*line != ' ' || !*line)
		return (1);
	printf("%c\n", *line);
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (1);
	if (color_extract(line, color) == 1)
		return (1);
	return (0);
}

int is_color(char *line, t_start *start)
{
	int res = 1;
	while (*line && *line == ' ')
		line++;
	if (ft_strncmp(line, "F", 1) == 0 && start->f_repeated == -1)
	{
		res = parse_color_line(line, &(start->floor));
		start->f_repeated++;
	}
	else if (ft_strncmp(line, "C", 1) == 0 && start->c_repeated == -1)
	{
		res = parse_color_line(line, &(start->ceiling));
		start->c_repeated++;
	}
	return (res);
}

/*int extract_color(char *pigment)
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
			printf("simbolos no numericos en el pigmento\n"); //Delete later
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
	color->a = 255;
	color->r = r;
	color->g = g;
	color->b = b;
	color->repeated = 0;
	color->rgba = (r << 24) | (g << 16) | (b<< 8) | color->a;
	return (0);
}

char *remove_trailing_comma(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len > 0 && str[len - 1] == ',')
        return ft_substr(str, 0, len - 1);
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
        free(palet[i]);
        palet[i] = temp;
        i++;
    }
}


int extract_pigment(char *pigment, char *chosen_pigemnt)
{
	int	num;

	num = ft_atoi(pigment);
	if (num >= 0 && num <= 255)
	{
		(*chosen_pigemnt) = num;
		return (0);
	}
	return (1);
}

int	check_pigment(char *line, int line_len, unsigned char pigment)
{
	int		i;
	char	*new_pigment;

	i = 0;
	if (line[0] = '-')
		return (1);
	if (*line == '+')
		line++;
	while (i < line_len)
	{
		if (line[i] == ' ')
			break;
		if (ft_isdigit(line[i]) == 0)
			return (1);
		i++;
	}
	if (i > 3)
		return (1);
	new_pigment = ft_substr(line, 0, 3);
	if (extract_pigment(new_pigment &pigment) == 1)
	{
		free(new_pigment);
		return (1); // error
	}
	free (new_pigment);
	return (0);
}

int	color_extract(char *line, t_color *color)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == '/0')
		return (1);
	if (line[i] !=  ',')
		return (1);
	if (check_pigment(line, i, color->r) == 1)
		return (1);
	
	// se hace la suma de todos pigmentos
	
	
}

int	parse_color_line (char *line, t_color *color)
{
	int	i;

	i = 0;
	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	if (*line != 'F' && *line != 'C')
		return (1);
	line++;
	while (*line && line == ' ')
	*line++;
	if (*line == '\0')
		return (1);
	if (color_extract(line, color->r) == 1)
		return (1);
	while (*line && line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	if (color_extract(line, color->g) == 1)
		return (1);
	while (*line && line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	if (color_extract(line, color->b) == 1)
		return (1);
	color->a = 255;
	color->rgba = r g b a (bit shifted);
	color->repeated++;
	return (0);
}

int	is_color(char *line, t_start *start)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	while (line[i] != '/0' && *line == ' ')
		line++;
	if (ft_strncmp(line[i], "F", 1) == 0 && start->floor.repeated == -1)
		res = check_line_for_color(line[i], &(start->floor));
	else if (ft_strncmp(line[i], "C", 1) == 0 && start->ceiling.repeated == -1)
		res = check_line_for_color(line[i], &(*start).ceiling);
	return (res);
}*/
