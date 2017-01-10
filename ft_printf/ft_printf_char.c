/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:47:45 by thendric          #+#    #+#             */
/*   Updated: 2017/01/02 11:55:55 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_convers_percent(t_input *input)
{
	int		flag;

	flag = 1;
	flag += ft_getflags(input);
	ft_checkflags(input, "%");
	input->form = input->form + flag;
	return (0);
}

int		ft_convers_c(t_input *input)
{
	int		flag;
	char	*c;

	flag = 1;
	c = ft_strnew(2);
	c[0] = (int)input->var;
	c[1] = '\0';
	flag += ft_getflags(input);
	ft_checkflags(input, c);
	input->form += flag;
	return (0);
}

int		ft_convers_s(t_input *input)
{
	int		flag;
	char	*str;

	flag = 1;
	str = (char *)input->var;
	if (!str)
		str = "(null)";
	flag += ft_getflags(input);
	str = ft_checkprecision(input, str);
	ft_checkflags(input, str);
	input->form += flag;
	return (0);
}

int		ft_convers_p(t_input *input)
{
	int		flag;
	int		num;
	char	*numstr;

	flag = 1;
	num = (int)input->var;
	numstr = ft_itoa_base(num, 16);
	flag += ft_getflags(input);
	numstr = ft_strjoin("0x10", numstr);
	ft_checkflags(input, numstr);
	input->form += flag;
	return (0);
}
