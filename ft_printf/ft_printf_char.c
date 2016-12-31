#include "ft_printf.h"

int 	ft_convers_percent(t_input *input)
{
	input->str = ft_strjoin(input->str, "%");
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_c(t_input *input)
{
	char 	*c;

	c = ft_strnew(2);
	c[0] = va_arg(input->ap, int);
	c[1] = '\0';
	input->str = ft_strjoin(input->str, c);
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_s(t_input *input)
{
	char *str;

	str = va_arg(input->ap, char *);
	input->str = ft_strjoin(input->str, str);
	//1 will be number of flags!
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_p(t_input *input)
{
	int num;
	char *numstr;

	num = va_arg(input->ap, int);
	numstr = ft_itoa_base(num, 16);
	input->str = ft_strjoin(input->str, "0x10");
	input->str = ft_strjoin(input->str, numstr);
	input->form += 1;
	return(0);
}