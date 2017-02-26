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

#include <fdf.h>

void	draw_circle(t_env *env, int x0, int y0, int x)
{
	env->color += 200;
	env->circle.y = 0;
	env->circle.err = 0;
	while (x >= env->circle.y)
	{
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 + env->circle.y, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 + env->circle.y, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 + env->circle.y, y0 + x, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 - env->circle.y, y0 + x, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 - x, y0 + env->circle.y, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 - x, y0 - env->circle.y, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 - env->circle.y, y0 - x, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 + env->circle.y, y0 - x, env->color);
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 - env->circle.y, env->color);
		if (env->circle.err <= 0)
		{
			env->circle.y += 1;
			env->circle.err += 2 * env->circle.y + 1;
		}
		if (env->circle.err > 0)
		{
			x -= 1;
			env->circle.err -= 2 * x + 1;
		}
	}
}

void	draw_line(t_env *env, int x0, int y0, int x1, int y1)
{
	env->line.dx = abs(x1 - x0);
	env->line.sx = x0 < x1 ? 1 : -1;
	env->line.dy = abs(y1 - y0);
	env->line.sy = y0 < y1 ? 1 : -1;
	env->line.err = (env->line.dx > env->line.dy ? env->line.dx : -env->line.dy) / 2;
	while (1)
	{
		mlx_pixel_put(env->mlx, env->window, x0, y0, COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		env->line.e2 = env->line.err;
		if (env->line.e2 > -env->line.dx)
		{
			env->line.err -= env->line.dy;
			x0 += env->line.sx;
		}
		if (env->line.e2 < env->line.dy)
		{
			env->line.err += env->line.dx;
			y0 += env->line.sy;
		}
	}
}

void	draw_grid(t_env *env)
{
	long	i;
	long	j;

	i = 0;
	j = 0;
	while (i < env->hght)
	{
		j = 0;
		while (j < env->wdth)
		{
			if (j < env->wdth - 1)
				draw_line(env, env->pnts[i][j].x, env->pnts[i][j].y, env->pnts[i][j + 1].x, env->pnts[i][j + 1].y);
			if (i < env->hght - 1)
				draw_line(env, env->pnts[i][j].x, env->pnts[i][j].y, env->pnts[i + 1][j].x, env->pnts[i + 1][j].y);
			j++;
		}
		i++;
	}
}
