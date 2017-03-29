#include "ft_ls.h"

void	get_options(t_all *lst, int argc, char *argv[])
{
	int i = 1;
	int j = 0;

	lst->options = 0x0;
	while (i < argc)
	{
		if (*argv[i])
		{
			j = 0;
			if (argv[i][j + 1] == '-')
				break ;
			while (*argv[i] == '-' && j < (int)ft_strlen(argv[i]))
			{
				if (argv[i][j] == 'a')
					lst->options += (0x1 << 1);
				else if (argv[i][j] == 'l')
					lst->options += (0x1 << 2);
				else if (argv[i][j] == 'R')
					lst->options += (0x1 << 3);
				else if (argv[i][j] == 'r')
					lst->options += (0x1 << 4);
				else if (argv[i][j] == 't')
					lst->options += (0x1 << 5);
				j++;
			}
		}
		i++;
	}
}