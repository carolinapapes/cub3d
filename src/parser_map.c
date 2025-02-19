/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:04:26 by kkoval            #+#    #+#             */
/*   Updated: 2025/02/19 19:21:25 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_map_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' \
	|| c == 'E')
		return (0);
	return (1);
}

int	is_one_view(char *map)
{
	int	letter_count;

	letter_count = 0;
	while (*map)
	{
		if (*map == 'N' || *map == 'S' || *map == 'W' || *map == 'E')
			letter_count++;
		if (letter_count > 1)
			return (1);
		map++;
	}
	if (letter_count != 1)
		return (1);
	return (0);
}

char	*find_first_map_line(char *input)
{
	int		i;

	while (*input)
	{
		while (*input != '\n')
			input++;
		while (*input == '\n')
			input++;
		i = 0;
		while (input[i] != '\0' && (is_map_character(input[i]) == 0 || input[i] == '\n'))
			i++;
		if (input[i] == '\0' && i != 0)
			return (input);
		input = &input[i];
	}
	return (NULL);
}

int	check_for_newlines_in_map(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			i++;
			if (map[i] == '\n')
			{
				while (map[i] != '\0' && map[i] == '\n')
					i++;
				if (map[i] == '\0')
					return (0);
				else
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_map(char *file_contents)
{
	char	*first_line;

	first_line = find_first_map_line(file_contents);
	if (first_line == NULL || *first_line == '\0')
	{
		printf("no hay primera linea\n");
		return (1);
	}
	printf("The map is: \n%s", first_line);
	if (is_one_view(first_line) == 1)
	{
		printf("There are more that one direction\n"); // TODO delete later
		return (1);
	}
	printf("%s\n", first_line); // TODO delete later
	if (check_for_newlines_in_map(first_line) == 1)
	{
		printf("%d  consecutive enter", check_for_newlines_in_map(first_line)); // TODO delete
		return (1);
	}
	return (0);
}

/*
int main(void) 
{
    char input[] = "lalalalala \n lalalalal\n\n10101S10110";
    if (check_map(input) == 1)
	{
		printf("error\n");
		return(1);
	}
    return (0);
}
*/