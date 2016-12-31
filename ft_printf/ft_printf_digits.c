#include "ft_printf.h"

int 	ft_convers_id(t_input *input)
{
	int flag;
	int num;
	char 	*numstr;

	flag = 1;
	num  = va_arg(input->ap, int);
	numstr = ft_itoa(num);
	flag += ft_getflags(input);
	ft_add_width(input, ft_strlen(numstr));
	input->str = ft_strjoin(input->str, numstr);
	//1 will be number of flags!
	input->form = input->form + flag;
	return (0);
}

int 	ft_convers_uU(t_input *input)
{
	long 	num;
	char 	*numstr;

	num  = va_arg(input->ap, int);
	// Could be better
	if (num < 0)
	{
		num += 4294967296;
	}
	//Need itoa with no int limit
	numstr = ft_itoa_base_long(num, 10);
	input->str = ft_strjoin(input->str, numstr);
	//1 will be number of flags!
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_f(t_input *input)
{
	double 	num;
	char 	*numstr;

	numstr = NULL;
	num  = va_arg(input->ap, double);
	//Create print number with decimal point
	//ft_putnbr(num);
	return (0);
}

int 	ft_convers_oO(t_input *input)
{
	int 	i;
	int 	flag;
	int 	num;
	char 	*numstr;

	i = 0;
	flag = 1;
	num  = va_arg(input->ap, int);
	numstr = ft_itoa_base(num, 8);
	flag += ft_getflags(input);
	ft_add_width(input, ft_strlen(numstr));
	while (input->flags[i])
	{
		if (input->flags[i] == '#')
			input->str = ft_strjoin(input->str, "0");
		i++;
		ft_bzero(input->flags, ft_strlen(input->flags));
	}
	input->str = ft_strjoin(input->str, numstr);
	input->form += flag;
	return (0);
}

int 	ft_convers_xX(t_input *input)
{
	int 	i;
	int 	flag;
	int 	num;
	char 	*numstr;

	i = 0;
	flag = 1;
	num  = va_arg(input->ap, int);
	numstr = ft_itoa_base(num, 16);
	ft_getflags(input);
	while (input->flags[i])
	{
		if (input->flags[i] == '#' && flag++)
		{
			if (ft_isupper(input->c))
				input->str = ft_strjoin(input->str, "0X");
			else
				input->str = ft_strjoin(input->str, "0x");
		}
		i++;
		ft_bzero(input->flags, ft_strlen(input->flags));
	}
	if (numstr && ft_isupper(input->c))
		ft_touppercase(numstr);
	input->str = ft_strjoin(input->str, numstr);
	input->form += flag;
	return (0);
}