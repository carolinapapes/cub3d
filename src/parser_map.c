#include <stdio.h>

int	is_map_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0);
	return (1);
}

int	is_valid_map_line(char *line) 
{
	int	letter_count;

	letter_count = 0;
	while (*line && *line != '\n')
	{
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
    		letter_count++;
        else if (is_map_character(*line))
            return (1);
        line++;
    }
	if (letter_count <= 1)
		return (0);
    return (1);
}

char* find_first_map_line(char *input)
{
	char	*line_start;

	line_start = input;
    while (*line_start) 
	{
		while (*line_start && *line_start != '\n' && is_map_character(*line_start))
            line_start++;
        if (*line_start && !is_map_character(*line_start))
		{
			if (is_valid_map_line(line_start) == 0)
        		return (line_start);
        }
        while (*line_start && *line_start != '\n')
        	line_start++;
        if (*line_start == '\n')
            line_start++;
    }
    return (NULL);
}

int	space_in_map(char *line)
{
	while(*line)
	{
		if (*line == '\n')
		{
			line++;
			while(*line && (*line == ' ' || *line == '\n'))
			{
				if (*line == '\n')
					return (1);
				line++;
				
			}
		}
		line++;
	}
	return (0);
}

int main(void) 
{
    char input[] = "Some header\nSome data\n\n\n111111\n10701\n   01  N\n1111111111\n045678098767\n\n";
    
    char *first_map_line = find_first_map_line(input);
    if (first_map_line)
        printf("First valid map line: %s\n", first_map_line);
    else
        printf("No valid map line found!\n");
    printf("%d\n", space_in_map(first_map_line));
    return (0);
}
