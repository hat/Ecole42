/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:47:45 by thendric          #+#    #+#             */
/*   Updated: 2017/01/13 14:37:06 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 		ft_convers_wc(t_input *input)
{
	wchar_t		c;
	unsigned	c_len;

	c_len = 0;
	c = (wchar_t)input->var;
	if (c <= 0x7F)
	{
		c_len = 1;
	}
	else if (c <= 0x7FF)
	{
		c_len = 2;
	}
	else if (c <= 0xFFFF)
	{
		c_len = 3;
	}
	else if (c <= 0x10FFFF)
	{
		c_len = 4;
	}
	return (c_len);
}

int 		ft_convers_ws(t_input *input)
{
	wchar_t		str;
	unsigned	c_len;

	c_len = 0;
	str = (wchar_t)input->var;
	if (str <= 0x7F)
	{
		c_len = 1;
	}
	else if (str <= 0x7FF)
	{
		c_len = 2;
	}
	else if (str <= 0xFFFF)
	{
		c_len = 3;
	}
	else if (str <= 0x10FFFF)
	{
		c_len = 4;
	}
	return (c_len);
}

// int		ft_convers_s(t_input *input)
// {
// 	int		flag;
// 	char	*str;

// 	flag = 1;
// 	str = (char *)input->var;
// 	if (!str)
// 		str = "(null)";
// 	flag += ft_getflags(input);
// 	ft_checkflags(input, str);
// 	input->form += flag;
// 	return (0);
// }
// int		ft_convers_c(t_input *input)
// {
// 	int		flag;
// 	char	*c;

// 	flag = 1;
// 	c = ft_strnew(2);
// 	c[0] = (int)input->var;
// 	c[1] = '\0';
// 	if (c[0] == 0)
// 		input->size++;
// 	flag += ft_getflags(input);
// 	ft_checkflags(input, c);
// 	input->form += flag;
// 	return (0);
// }