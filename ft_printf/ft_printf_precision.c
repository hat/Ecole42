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
  char *fill;
  
  //Check to make sure it's not anything but numbers rather than just not s
  if (input->precision > (int)ft_strlen(str) && input->c != 's' && input->c != 'c')
  {
    fill = ft_strnew(input->precision - ft_strlen(str));
    ft_memset(fill, '0', input->precision - ft_strlen(str));
    new = ft_strjoin(fill, str);
    //ft_memdel((void **)&fill);
  }
  else
  {
    if (input->precision != -1 && input->c == 's')
      new = ft_strndup(str, input->precision);
    else if (input->precision == 0 && input->c != '%')
      new = ft_strndup(str, input->precision);
    else
      new = ft_strdup(str);
  }
  //if input->c == s it has not been allocated!
  //ft_memdel((void **)&str);
  return (new);
}
