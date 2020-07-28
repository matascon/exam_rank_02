#include <unistd.h>

int	main(int argc, char **argv)
{
	unsigned char	chars[255];
	int				i;
	int				j;

	i = -1;
	while (i++ < 255)
	chars[i] = '\0';
	if (argc == 3)
	{
		i = 1;
		while (i < argc)
		{
			j = 0;
			while (argv[i][j])
			{
				if (!(chars[argv[i][j]]))
				{
					write(1, &argv[i][j], 1);
					chars[argv[i][j]] = argv[i][j];
				}
				j++;
			} 
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
