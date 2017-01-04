#include "ft_printf.h"

char	*ft_flagspace(char *str)
{
	char	*new;

	new = ft_strjoin(" ", str);
	ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagpound(t_input *input, char *str)
{
	char	*prefix;
	char	*new;

	if (ft_getconversion(input->form) == 'x')
		prefix = ft_strdup("0x");
	if (ft_getconversion(input->form) == 'X')
		prefix = ft_strdup("0X");
	if (ft_getconversion(input->form) == 'o')
		prefix = ft_strdup("0");
	if (ft_getconversion(input->form) == 'O')
		prefix = ft_strdup("0");
	new = ft_strjoin(prefix, str);
	if (new && ft_isupper(input->c))
		ft_touppercase(new);
	ft_memdel((void **)&prefix);
	ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagplus(char *str)
{
	char	*new;

	new = ft_strjoin("+", str);
	ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagwidth(t_input *input, char *str, int left)
{
	int 	i;
	int 	offset;
	char 	*fill;

	i = 0;
	offset = ft_strlen(str);
	fill = ft_strnew(1);
	fill[0] = ' ';
	if (!input->flagminus && input->flagzero)
		fill[0] = '0';
	if (input->flagpound && ft_tolower(input->c) == 'x')
		offset += 2;
	if (input->flagpound && ft_tolower(input->c) == 'o')
		offset += 1;
	//HUGE MEMORY LEAK -- WHAT DO I DO?!?!?
	while (input->width-- > offset)
	{
		if (left)
			str = ft_strjoin(str, fill);
		else
			str = ft_strjoin(fill, str);
	}
	ft_memdel((void **)&fill);
	return (str);
}
