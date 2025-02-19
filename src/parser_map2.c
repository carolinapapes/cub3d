/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:13:18 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/19 19:51:36 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

int	is_map_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' \
	|| c == 'E')
		return (0);
	return (1);
}

//more serious check for map to then pass it to start strut and play around

int	ft_map_start(char **file)
{
	int		l;
	int		i;
	int		start;

	l = 0;
	start = -1;
	while (file[l] != NULL)
	{
		i = 0;
		while (file[l][i] != '\0' && (is_map_character(file[l][i]) == 0))
			i++;
		if (file[l][i] != '\0')
		{
			l++;
			start = -1;
		}
		else
		{
			if (start == -1)
				start = l;
		}
		l++;
	}
	return (start);
}

int	check_empty_lines_in_map(char **file)
{
	int	line;
	int	i;

	line = ft_map_start(file);
	printf("%d\n", line);
	if (line == -1)
		return (1);
	while (file[line] != NULL)
	{
		printf("me he quedado atascado\n");
		i = 0;
		while (file[line][i] != '\0')
		{
			if (file[line][0] == ' ')
			{
				while (file[line][i] != '\0' && file[line][i] == ' ')
					i++;
				if (file[line][i] == '\0')
					return (1);
				else
					break;
			}
			i++;
		}
		line++;
	}
	return (0);
}

int	main(void)
{
	char	**test;

	test = malloc(sizeof(char *) * 6);
	if (!test)
		return (0);
	test[0] = "   ";
	test[1] = "10 11 E 111";
	test[2] = "1111111111111";
	test[3] = "ko";
	test[4] = "101010";
	test[5] = NULL;
	printf("%d\n", check_empty_lines_in_map(test));
	return(0);
}