#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	char	*text;
	int	fd;

	fd = open("salu2", O_RDONLY);
	printf("%i ---> ", get_next_line(fd, &text));
	printf("%s\n", text);
	free(text);
	printf("%i ---> ", get_next_line(fd, &text));
        printf("%s\n", text);
	free(text);
	printf("%i ---> ", get_next_line(fd, &text));
        printf("%s\n", text);
	free(text);
	printf("%i ---> ", get_next_line(fd, &text));
        printf("%s\n", text);
	free(text);
	close(fd);
	return (0);
}
