/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_universal_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:51:30 by thendric          #+#    #+#             */
/*   Updated: 2017/01/13 15:05:59 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	ft_vartype(t_input *input)
{
	int				i;
	int				num;
	long			num_long;
	short			num_short;
	signed char		char_signed;
	ssize_t			num_sizet;
	unsigned long	num_unsignl;
	int				islong;
	int				is_h;
	int				is_z;

	i = 0;
	islong = 0;
	is_h = 0;
	is_z = 0;
	while (input->flags[i])
	{
		if (input->flags[i] == 'l' || input->flags[i] == 'j')
			islong++;
		if (input->flags[i] == 'h')
			is_h++;
		if (input->flags[i] == 'z')
			is_z++;
		i++;
	}
	if (input->c == 'u' || input->c == 'U')
	{
		num_unsignl = (unsigned long)input->var;
		return (num_unsignl);
	}
	if (islong)
	{
		num_long = (long)input->var;
		return (num_long);
	}
	if (is_h == 1)
	{
		num_short = (short)input->var;
		return (num_short);
	}
	else if (is_h == 2)
	{
		char_signed = (signed char)input->var;
		return (char_signed);
	}
	else if (is_z)
	{
		num_sizet = (size_t)input->var;
		return (num_sizet);
	}
	else
		num = (int)input->var;
	return (num);
}

char	ft_getconversion(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_isconversion(str[i]))
			return (str[i]);
		i++;
	}
	return (' ');
}

int		ft_isflag(char c)
{
	if (c == '#' || c == '-' || c == '0')
	{
		return (1);
	}
	return (0);
}

int		ft_isconversion(char c)
{
	if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f' || c == 'o' || c == 'x'
			|| c == 'u' || c == 'O' || c == 'X' || c == 'p'
			|| c == 'U' || c == 'D' || c == 'C')
	{
		return (1);
	}
	return (0);
}
