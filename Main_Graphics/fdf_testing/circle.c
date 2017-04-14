/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:08:48 by thendric          #+#    #+#             */
/*   Updated: 2017/01/31 20:16:38 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(t_env *env, int x0, int y0, int x)
{
	env->crcl.y = 0;
	env->crcl.err = 0;
	while (x >= env->crcl.y)
	{
		mlx_pixel_put(env->mlx, env->win, x0 + x, y0 + env->crcl.y, env->clr1);
		mlx_pixel_put(env->mlx, env->win, x0 + x, y0 + env->crcl.y, env->clr2);
		mlx_pixel_put(env->mlx, env->win, x0 + env->crcl.y, y0 + x, env->clr1);
		mlx_pixel_put(env->mlx, env->win, x0 - env->crcl.y, y0 + x, env->clr2);
		mlx_pixel_put(env->mlx, env->win, x0 - x, y0 + env->crcl.y, env->clr1);
		mlx_pixel_put(env->mlx, env->win, x0 - x, y0 - env->crcl.y, env->clr2);
		mlx_pixel_put(env->mlx, env->win, x0 - env->crcl.y, y0 - x, env->clr1);
		mlx_pixel_put(env->mlx, env->win, x0 + env->crcl.y, y0 - x, env->clr2);
		mlx_pixel_put(env->mlx, env->win, x0 + x, y0 - env->crcl.y, env->clr1);
		if (env->crcl.err <= 0)
		{
			env->crcl.y += 1;
			env->crcl.err += 2 * env->crcl.y + 1;
		}
		if (env->crcl.err > 0)
		{
			x -= 1;
			env->crcl.err -= 2 * x + 1;
		}
	}
}
