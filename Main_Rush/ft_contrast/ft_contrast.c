/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:33:27 by thendric          #+#    #+#             */
/*   Updated: 2017/04/09 13:43:03 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_tpool.h>

void my_job_to_exec(void *param)
{
  t_my_data_struct *my;

  my=(t_my_data_struct *)param;
  if ()// I do something wih my->ret work)
    my->ret=SUCCESS;
  else
    my->ret=FAILURE;
}

int main(int ac, char **av)
{
  t_tp_thread *my_tp;
  t_my_data_struct *data;

  my_tp=tp_create(8);
  tp_add_task(my_tp, my_job_to_exec, (void *)data); //we can add several jobs
  tp_wait_for_queue(my_tp);
  if (data->ret == SUCCESS)
  //that was a success
  else
  //that was a failure
}
