#include <stdio.h>
#include "cube3d.h"

int ft_ispace(char c) {
    if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f') 
        return 1;
    return 0;
}

int count_lines(const char *s) 
{
    int i;
    int lines;
    int newlines_in_a_row;

	i = 0;
	lines = 0;
	newlines_in_a_row = 0;
    while (s[i] != '\0')
    {
		if (s[i] == '\n') 
		{
			lines++;
            newlines_in_a_row = 1;
            i++;
            while (s[i] != '\0' && (s[i] == '\n' || ft_ispace(s[i])))
            {
                if (s[i] == '\n') 
                    newlines_in_a_row++;
                i++;
            }
            if (newlines_in_a_row > 1)
			{
				lines++;
			}
        }
        else 
            i++;
    }
    return lines;
}


int main() {
    const char *testStr1 = "\n   \n\n"; // 1 line for multiple newlines
    const char *testStr2 = "\n   \n hola"; // 2 lines: one for newlines, one for 'hola'
    const char *testStr3 = "hola \n\n"; // 2 lines: one for 'hola', one for newlines
    const char *testStr4 = "hi. \n my name is Janice, \n.  \n bye \n\n"; // 5 lines

    printf("Line count (testStr1): %d\n", count_lines(testStr1)); // Expected: 1
    printf("Line count (testStr2): %d\n", count_lines(testStr2)); // Expected: 2
    printf("Line count (testStr3): %d\n", count_lines(testStr3)); // Expected: 2
    printf("Line count (testStr4): %d\n", count_lines(testStr4)); // Expected: 5

    return 0;
}



/*
int main() {
	char **file_lines;
	int i = 0;
    const char *text = "\n\nhola\n me gusta el cafe/n   /n/n/n";
    printf("Line count: %d\n", count_lines(text));
	file_lines = ft_split_newline(text);
	while (file_lines[i] != NULL)
	{
		printf("%s\n", file_lines[i]);
		i++;
	}
    return 0;
}*/