#include "ft_printf.h"

char	*ft_addnegative(t_input *input, char *str)
{
	char	*new;

	input->negative = input->negative;
	//input->negative = 0;
	new = ft_strnew(ft_strlen(str) + 1);
	new++;
	new = ft_strdup(str);
	new--;
	new[0] = '-';
	//ft_memdel((void **)&str);
	return (new);
}

char	*ft_deletenegative(t_input *input, char *str)
{
	char	*new;

	input->negative = 1;
	new = ft_strnew(ft_strlen(str - 1));
	new = ft_strdup(str + 1);
	//ft_memdel((void **)&str);
	return (new);
}
