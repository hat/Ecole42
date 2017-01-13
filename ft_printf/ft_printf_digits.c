/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_digits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:48:42 by thendric          #+#    #+#             */
/*   Updated: 2017/01/02 11:54:01 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_convers_id(t_input *input)
{
	int		flag;
	long		num;
	char	*numstr;

	flag = 1;
	flag += ft_getflags(input);
	num = ft_vartype(input);
	numstr = ft_itoa_base_long(num, 10);
	ft_checkflags(input, numstr);
	input->form = input->form + flag;
	return (0);
}

int		ft_convers_uUD(t_input *input)
{
	int		flag;
	long	num;
	char	*numstr;

	flag = 1;
	flag += ft_getflags(input);
	num = ft_vartype(input);
	if (num < 0)
		num += 4294967296;
	numstr = ft_itoa_base_long(num, 10);
	ft_checkflags(input, numstr);
	input->form = input->form + flag;
	return (0);
}

int		ft_convers_f(t_input *input)
{
	input = NULL;
	return (0);
}

int		ft_convers_oO(t_input *input)
{
	int		i;
	int		flag;
	long	num;
	char	*numstr;

	i = 0;
	flag = 1;
	flag += ft_getflags(input);
	num = (long)input->var;
	numstr = ft_itoa_base(num, 8);
	ft_checkflags(input, numstr);
	input->form += flag;
	return (0);
}

int		ft_convers_xX(t_input *input)
{
	int		flag;
	long	num;
	char	*numstr;

	flag = 1;
	flag += ft_getflags(input);
	num = ft_vartype(input);
	numstr = ft_itoa_base_long(num, 16);
	ft_checkflags(input, numstr);
	input->form += flag;
	return (0);
}
