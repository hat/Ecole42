#include "ft_ls.h"

void set_flags(t_all *lst, char *argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		lst->flags = (argv[i] == 'a' && !check_bit(lst->flags, 1))
			? lst->flags += (0x1 << 1) : lst->flags;
		lst->flags = (argv[i] == 'l' && !check_bit(lst->flags, 1))
			? lst->flags += (0x1 << 2) : lst->flags;
		lst->flags = (argv[i] == 'R' && !check_bit(lst->flags, 1))
			? lst->flags += (0x1 << 3) : lst->flags;
		lst->flags = (argv[i] == 'r' && !check_bit(lst->flags, 1))
			? lst->flags += (0x1 << 4) : lst->flags;
		lst->flags = (argv[i] == 't' && !check_bit(lst->flags, 1))
			? lst->flags += (0x1 << 5) : lst->flags;
		i++;
	}
}

void	get_options(t_all *lst, int argc, char *argv[])
{
	int i;
	int end;

	i = 0;
	end = 0;
	lst->flags = 0x0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
		{
			if (argv[i][1] == '-')
				break ;
			else if (*argv[i] == '-' && !end)
				set_flags(lst, argv[i]);
			else
				ft_printf("ls: %s: No such file or directory\n", argv[i]);
		}
		else
			end = 1;
	}
}
