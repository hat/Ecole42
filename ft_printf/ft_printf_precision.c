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

char    *ft_checkprecision(t_input *input, char *str)
{
  char *new;
  
  if (input->precision != -1 && input->precision > (int)ft_strlen(str))
    new = ft_strndup(str, input->precision);
  else if (input->precision != -1 && input->c == 's')
    new = ft_strndup(str, input->precision);
  else if (input->precision == 0)
    new = ft_strndup(str, input->precision);
  else
    new = ft_strdup(str);
  return (new);
}
