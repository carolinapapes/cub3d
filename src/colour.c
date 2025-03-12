/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/12 16:56:24 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		//printf("%s\n", palet[i]); //Delete after better coma handeling
		i++;
	}
	fix_palet(palet);
	i = 0;
	while(palet[i] != NULL)
	{
		//printf("|%s|\n", palet[i]); //Delete later
		i++;
	}
	if (ft_strncmp(palet[0], "F", 1) == 0 && start->floor.repeated == -1)
		res = check_line_for_color(palet, &(start->floor));
	else if (ft_strncmp(palet[0], "C", 1) == 0 && start->ceiling.repeated == -1)
		res = check_line_for_color(palet, &(*start).ceiling);
	free_char_array(&palet);
	return (res);
}
