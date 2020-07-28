#include <unistd.h>

int	main(int argc, char **argv)
{
	int 			i;
	int				j;
	unsigned char	chars[255];

	i = -1;
	while (++i < 255)
		chars[i] = 0;
	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			j = 0;
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					if (!(chars[argv[2][j]]))
					{
						write(1, &argv[1][i], 1);
						chars[argv[1][i]] = 1;
					}	
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
