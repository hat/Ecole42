#include "ft_printf.h"

//ONE OF THE MEM DELETES IN HERE WAS CAUSING ISSUES!!!

char	*ft_flagspace(char *str)
{
	char	*new;

	if (ft_strcmp(str, ""))
		new = ft_strjoin(" ", str);
	else
		new = ft_strdup(str);
	//ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagpound(t_input *input, char *str)
{
	char	*prefix;
	char	*new;

	if (ft_getconversion(input->form) == 'x' && input->precision != 0)
		prefix = ft_strdup("0x");
	else if (ft_getconversion(input->form) == 'X' && input->precision != 0)
		prefix = ft_strdup("0X");
	else if (ft_getconversion(input->form) == 'o')
		prefix = ft_strdup("0");
	else if (ft_getconversion(input->form) == 'O')
		prefix = ft_strdup("0");
	new = ft_strjoin(prefix, str);
	if (new && ft_isupper(input->c))
		ft_touppercase(new);
	//ft_memdel((void **)&prefix);
	//ft_memdel((void **)&str);
	return (new);
}

char	*ft_flagplus(char *str)
{
	char	*new;

	new = ft_strjoin("+", str);
	//ft_memdel((void **)&str);
	return (new);
}

int 	ft_widthoffset(t_input *input, char	*str)
{
	int 	offset;

	offset = ft_strlen(str);
	if (input->c == 'c' && !*str)
		offset += 1;
	if ((input->flagplus || input->negative) && str[0] != '-')
		offset += 1;
	if (input->flagpound && ft_tolower(input->c) == 'x' && (input->flagminus || input->flagzero))
		offset += 2;
	if (input->flagpound && ft_tolower(input->c) == 'o' && (input->flagminus || input->flagzero))
		offset += 1;
	return (offset);
}

char	*ft_flagwidth(t_input *input, char *str, int left)
{
	int 	i;
	int 	offset;
	char 	fill;
	char	*width;
	char	*new;

	i = 0;
	fill = ' ';
	if (!input->flagminus && input->flagzero)
		fill = '0';
	if (input->precision != -1 && input->flagzero && input->precision < input->width)
		fill = ' ';
	offset = ft_widthoffset(input, str);
	width = ft_strnew(input->width);
	if (input->width - offset > 0)
		ft_memset(width, fill, input->width - offset);
	if (left)
		new = ft_strjoin(str, width);
	else
		new = ft_strjoin(width, str);
	//ft_memdel((void **)&width);
	//ft_memdel((void **)&str);
	return (new);
}
