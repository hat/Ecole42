/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:50:11 by thendric          #+#    #+#             */
/*   Updated: 2017/01/02 11:54:52 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//WIDTH AND # FLAGS COINCIDE WITH EACH OTHER!!!!
//REALLY THINK ABOUT THE ORDER OF THE FLAGS AND CHANGING THE STRING!!!

long	ft_vartype(t_input *input)
{
	int 	i;
	long	num;
	int 	islong;

	i = 0;
	islong = 0;
	while (input->flags[i])
	{
		if (input->flags[i] == 'l' || input->flags[i] == 'j')
			islong++;
		i++;
	}
	if (islong)
		num = (long)input->var;
	else
		num = (int)input->var;
	return (num);
}

char	*ft_flagspace(char *str)
{
	str = ft_strjoin(" ", str);
	return (str);
}

char	*ft_flagpound(t_input *input, char *str, int upper)
{
	char	*prefix;

	if (ft_getconversion(input->form) == 'x')
		prefix = ft_strdup("0x");
	else if (ft_getconversion(input->form) == 'X')
		prefix = ft_strdup("0X");
	else if (ft_getconversion(input->form) == 'o')
		prefix = ft_strdup("0");
	else if (ft_getconversion(input->form) == 'O')
		prefix = ft_strdup("0");
	else
		printf("Error ft_flagpound\n");
	if (upper)
		str = ft_strjoin(prefix, str);
	else
		str = ft_strjoin(prefix, str);
	if (str && upper)
		ft_touppercase(str);
	return (str);
}

char	*ft_flagplus(char *str)
{
	str = ft_strjoin("+", str);
	return (str);
}

int		ft_atoi_flags(const char *str)
{
	int		ans;
	int		i;
	int		neg;

	ans = 0;
	i = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32 || ft_isflag(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ans = (ans * 10) + (str[i] - '0');
		i++;
	}
	return (ans * neg);
}

int		ft_getflags(t_input *input)
{
	int		i;
	char	*c;

	i = 1;
	c = ft_strdup(input->form + 1);
	while (input->form[i] && !ft_isconversion(ft_tolower(input->form[i])))
		i++;
	c[i - 1] = '\0';
	input->flags = ft_strjoin(input->flags, c);
	input->width = ft_atoi_flags(input->flags);
	i = 0;
	while (input->flags[i] && input->flags[i] != '.')
		i++;
	input->precision = ft_atoi_flags(&input->flags[i + 1]);
	return (ft_strlen(input->flags));
}

//Need all checks that will eventually add length to str
//or change the getwidth function
char	*ft_addwidth(t_input *input, char *str)
{
	int 	i;
	int 	offset;
	int 	leftjustify;
	char 	*fill;

	i = 0;
	offset = ft_strlen(str);
	leftjustify = 0;
	fill = ft_strnew(1);
	fill[0] = ' ';
	while (ft_isflag(input->flags[i]))
	{
		if (input->flags[i] == '0')
			fill[0] = '0';
		if (input->flags[i] == '-')
			leftjustify++;
		if (input->flags[i] == '#' && ft_tolower(input->c) == 'x')
			offset += 2;
		if (input->flags[i] == '#' && ft_tolower(input->c) == 'o')
			offset += 1;
		i++;
	}
	while (input->width-- > offset)
	{
		if (!leftjustify)
			str = ft_strjoin(fill, str);
		else
			str = ft_strjoin(str, fill);
	}
	return (str);
}
//UPPER NOT USED BUT MAY BE BETTER??!?!?!?!?


//Still used for percent, c, c, p
void	ft_add_width(t_input *input, size_t var_size, char *str)
{
	int		i;
	int		leftjustify;
	char	*fill;

	i = 0;
	leftjustify = 0;
	fill = ft_strnew(1);
	fill[0] = ' ';
	while (ft_isflag(input->flags[i]))
	{
		if (input->flags[i] == '-')
		{
			fill[0] = ' ';
			leftjustify++;
		}
		if (input->flags[i] == '0' && !leftjustify)
			fill[0] = '0';
		i++;
	}
	if (leftjustify)
		input->str = ft_strjoin(input->str, str);
	while (input->width-- > (int)var_size)
		input->str = ft_strjoin(input->str, fill);
	if (!leftjustify)
		input->str = ft_strjoin(input->str, str);
	ft_bzero(input->flags, ft_strlen(input->flags));
}

char	*ft_checkcon_cap(t_input *input, char *str)
{
	if (ft_getconversion(input->form) == 'X')
		ft_touppercase(str);
	return (str);
}

//NEEDS TO CHECK IF A FLAG EXISTS ONLY ONCE NOT MANY TIMES
//USE EITHER AN ARRAY OR ADD EACH ONE TO STRUCT...
//MOST LIKELY ADD TO STRUCT!!!
void	ft_checkflags(t_input *input, char *str)
{
	int		i;

	i = 0;
	//str = ft_addwidth(input, str);
	while (input->flags[i])
	{
		if (input->flags[i] == '+')
			str = ft_flagplus(str);
		if (input->flags[i] == '#' && ft_strcmp(str, "0"))
			str = ft_flagpound(input, str, ft_isupper(input->c));
		if (input->flags[i] == ' ' && ft_strlen(input->flags) == 1 && str[0] != '-')
			str = ft_flagspace(str);
		i++;
	}
	//str = ft_checkcon_cap(input, str);
	//input->str = ft_strjoin(input->str, str);
	ft_add_width(input, ft_strlen(str), str);
	if (input->c == 'X')
		ft_touppercase(input->str);
}
