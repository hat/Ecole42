#include "ft_printf.h"

int 	ft_isconversion(char c)
{
	if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f' || c == 'o' || c == 'x'
			|| c == 'u' || c == 'O' || c == 'X' || c == 'p'
			|| c == 'U' || c == 'D')
	{
		return (1);
	}
	return (0);
}

char	ft_getconversion(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (ft_isconversion(str[i]))
			return (str[i]);
		i++;
	}
	return ' ';
}

int		ft_isflag(char c)
{
	if (c == '#' || c == '-' || c == '0')
	{
		return (1);
	}
	return (0);
}
