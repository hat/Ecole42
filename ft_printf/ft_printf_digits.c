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
	ft_checkflags(input, numstr);
	input->form = input->form + flag;
	return (0);
}

int 	ft_convers_uUD(t_input *input)
{
	int 	flag;
	long 	num;
	char 	*numstr;

	flag = 1;
	num  = va_arg(input->ap, int);
	if (num < 0)
		num += 4294967296;
	numstr = ft_itoa_base_long(num, 10);
	flag += ft_getflags(input);
	ft_checkflags(input, numstr);
	input->form = input->form + flag;
	return (0);
}

//TODO Create decimal place itoa
int 	ft_convers_f(t_input *input)
{
	input = NULL;
	// double 	num;
	// char 	*numstr;

	// numstr = NULL;
	// num  = va_arg(input->ap, double);
	// ft_checkflags(input, numstr);
	//Create print number with decimal point
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
	//Checking for + flag doesn't need to be done for o or O
	ft_checkflags(input, numstr);
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
	flag += ft_getflags(input);
	//Checking for + flag doesn't need to be done for o or O
	ft_checkflags(input, numstr);
	input->form += flag;
	return (0);
}
