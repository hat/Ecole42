#include "ft_printf.h"

char	*ft_flagspace(char *str)
{
	char	*new;

	if (ft_strcmp(str, ""))
		new = ft_strjoin(" ", str);
	else
		new = ft_strdup(str);
	ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagpound(t_input *input, char *str)
{
	char	*prefix;
	char	*new;

	if (ft_getconversion(input->form) == 'x')
		prefix = ft_strdup("0x");
	else if (ft_getconversion(input->form) == 'X')
		prefix = ft_strdup("0X");
	else if (ft_getconversion(input->form) == 'o')
		prefix = ft_strdup("0");
	else if (ft_getconversion(input->form) == 'O')
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
	char 	fill;
	char	*width;
	char	*new;

	i = 0;
	offset = ft_strlen(str);
	fill = ' ';
	if (input->c == 'c' && !*str)
		offset += 1;
	if (!input->flagminus && input->flagzero)
		fill = '0';
	if (input->flagpound && ft_tolower(input->c) == 'x' && (input->flagminus || input->flagzero))
		offset += 2;
	if (input->flagpound && ft_tolower(input->c) == 'o' && (input->flagminus || input->flagzero))
		offset += 1;
	width = ft_strnew(input->width);
	if (input->width - offset > 0)
		ft_memset(width, fill, input->width - offset);
	if (left)
		new = ft_strjoin(str, width);
	else
		new = ft_strjoin(width, str);
	ft_memdel((void **)&width);
	ft_memdel((void **)&str);
	return (new);
}
