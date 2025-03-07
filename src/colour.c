/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:35:14 by kkoval            #+#    #+#             */
/*   Updated: 2025/03/07 13:38:04 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int ft_atoi(const char *str)
{
	int res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int parse_color_component(char **line)
{
	int value;

	while (**line == ' ')
		(*line)++;
	if (**line < '0' || **line > '9')
		return (-1);
	value = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line == ' ')
		(*line)++;
	return (value);
}

int extract_color(t_color *color, char *line)
{
	int r;
	int	g;
	int	b;

	while (*line == ' ')
		line++;
	if (*line != 'F' && *line != 'C')
		return (1);
	line++;
	while (*line == ' ')
		line++;
	r = parse_color_component(&line);
	if (*line != ',')
		return (1);
	line++;
	g = parse_color_component(&line);
	if (*line != ',')
		return (1);
	line++;
	b = parse_color_component(&line);
	if (*line != '\0' && *line != ' ')
		return (1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	color->r = (unsigned char)r;
	color->g = (unsigned char)g;
	color->b = (unsigned char)b;
	color->a = 255;
	color->rgba = (color->r << 24) | (color->g << 16) | (color->b<< 8) | 255;
	return (0);
}

int check_line_for_color(t_color *floor, t_color *ceiling, char **elements)
{
	int line;
	int f_count;
	int c_count;

	line = 0;
	f_count = 0;
	c_count = 0;
	while (elements[line] != NULL)
	{
		if (strstr(elements[line], "F") != NULL)
		{
			if (extract_color(floor, elements[line]) == 0)
				f_count++;
		}
		else if (strstr(elements[line], "C") != NULL)
		{
			if (extract_color(ceiling, elements[line]) == 0)
				c_count++;
		}
		line++;
	}
	if (c_count != 1|| f_count != 1)
		return (1);
	return (0);
}

int	check_for_color(t_start *start, char **elements)
{
	if (check_line_for_color(&(*start).floor, &(*start).ceiling, elements) == 1)
	{
		printf("no hay colorsitos para el suelo o para el cielo :(\n");
		return (1);
	}
	printf("ceiling colours r: %d, b: %d, g: %d  color total es: %d\n", start->ceiling.r, start->ceiling.b, start->ceiling.g, start->ceiling.rgba);
	printf("floor colours r: %d, b: %d, g: %d color total es: %d\n", start->floor.r, start->floor.b, start->floor.g, start->floor.rgba);
	return (0);
}

/*int main(void)
{
	t_color floor;
	t_color ceiling;

	// Test input cases
	char *elements1[] = {
		"     F   220, 100,   8   ", // Floor color
		"     C  50,   50, -50 ",     // Ceiling color
		NULL
	};

	char *elements2[] = {
		"F 255, 255, 255",
		"C 0, 5, 0",
		NULL
	};

	char *elements3[] = {
		"     F  128, 64, 32  ",
		"     C 255, 255, 255  ",
		"     C 200, 200, 200  ",
		NULL
	};

	char *elements4[] = {
		"     F  300, 50, 0  ",
		"     C 0, 0, 255  ",
		NULL
	};

	printf("Test 1:\n");
	if (check_line_for_color(&floor, &ceiling, elements1) == 0)
		printf("Floor: R=%d, G=%d, B=%d\nCeiling: R=%d, G=%d, B=%d\n\n",
			floor.r, floor.g, floor.b, ceiling.r, ceiling.g, ceiling.b);

	printf("Test 2:\n");
	if (check_line_for_color(&floor, &ceiling, elements2) == 0)
		printf("Floor: R=%d, G=%d, B=%d\nCeiling: R=%d, G=%d, B=%d\n\n",
			floor.r, floor.g, floor.b, ceiling.r, ceiling.g, ceiling.b);

	printf("Test 3 (Error expected - duplicate C):\n");
	check_line_for_color(&floor, &ceiling, elements3);
	printf("\n");

	printf("Test 4 (Error expected - invalid RGB value):\n");
	check_line_for_color(&floor, &ceiling, elements4);
	printf("\n");


	return (0);
}*/

/*int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int extract_color(char *line, t_color *color)
{
	int r, g, b;
	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return 1;

	// Extract Red
	r = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line++ != ',') return 1;  // Expecting a comma after red

	// Extract Green
	g = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line++ != ',') return 1;  // Expecting a comma after green

	// Extract Blue
	b = ft_atoi(line);
	while (*line && (*line == ' ' || *line == '\0'))
		line++;

	// Check for valid color ranges
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return 1;

	// Set the color values in the union
	color->r = (unsigned char)r;
	color->g = (unsigned char)g;
	color->b = (unsigned char)b;
	color->a = 0;

	// Combine into a single integer value (rgba) using bit shifting
	color->rgba = (color->r << 16) | (color->g << 8) | color->b;

	return 0;
}

int	is_letter(char *line, char chr, t_color *color)
{
	while (*line && *line == ' ')
		line++;
	if (*line == '\0' || *line != chr)
		return (1);
	if (extract_color(line, color) == 1)
		return (1);
	return (0);
}

int	check_line_for_color(t_start *start, char **elements)
{
	int	i;
	int	c_count;
	int	f_count;

	i = 0;
	c_count = 0;
	f_count = 0;
	while (elements[i] != NULL)
	{
		if (is_letter(elements[i], 'C', &(start->ceiling)) == 0)
			c_count++;
		else if (is_letter(elements[i], 'F', &(start->floor)) == 0)
			f_count++;
		if (c_count > 1 || f_count > 1)
			return (1);
		i++;
	}
	if (c_count != 1 || f_count != 1)
		return (1);
	return (0);
}

int	check_for_color(t_start *start, char **elements)
{
	if (check_line_for_color(start, elements) == 1)
	{
		printf("no hay colorsitos para el suelo o para el cielo :(\n");
		return (1);
	}
	return (0);
}

int	main(void)
{
	t_start	start;
	char	*test_lines[] = {
		"C 20,100,1",
		"F 20, 54, 4  ",
		NULL
	};

	if (check_for_color(&start, test_lines) == 0)
	{
		printf("Ceiling Color: R=%d, G=%d, B=%d, A=%d\n",
			start.ceiling.r, start.ceiling.g, start.ceiling.b, start.ceiling.a);
		printf("Floor Color: R=%d, G=%d, B=%d, A=%d\n",
			start.floor.r, start.floor.g, start.floor.b, start.floor.a);
	}
	else
	{
		printf("Error: Invalid colors\n");
	}
	return (0);
}*/