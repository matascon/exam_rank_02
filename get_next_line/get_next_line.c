#include "get_next_line.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	str = (char *)malloc(i + 2);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = s2[0];
	str[j] = '\0';
	free(s1);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char	*buffer;
	int		n_bytes;

	if (!line || !(buffer = (char *)malloc(2)) \
	|| !(*line = (char *)malloc(1)))
		return (-1);
	(*line)[0] = '\0';
	while ((n_bytes = read(fd, buffer, 1)) > 0)
	{
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break;
		*line = ft_strjoin(*line, buffer);
	}
	free(buffer);
	return (n_bytes);
}
