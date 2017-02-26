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
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 + y, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 + y, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 + y, y0 + x, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 - y, y0 + x, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 - x, y0 + y, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 - x, y0 - y, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 - y, y0 - x, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 + y, y0 - x, COLOR);
		mlx_pixel_put(env->mlx, env->window, x0 + x, y0 - y, COLOR);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void	draw_line(t_env *env, int x0, int y0, int x1, int y1)
{
	env->dx = abs(x1 - x0);
	env->sx = x0 < x1 ? 1 : -1;
	env->dy = abs(y1 - y0);
	env->sy = y0 < y1 ? 1 : -1;
	env->err = (env->dx > env->dy ? env->dx : -env->dy) / 2;

	while (1)
	{
		mlx_pixel_put(env->mlx, env->window, x0, y0, COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		env->e2 = env->err;
		if (env->e2 > -env->dx)
		{
			env->err -= env->dy;
			x0 += env->sx;
		}
		if (env->e2 < env->dy)
		{
			env->err += env->dx;
			y0 += env->sy;
		}
	}
}

void	draw_box(t_env *env, int x0, int y0, int x1, int y1)
{
	draw_line(env, x0, y0, x0, y1);
	draw_line(env, x0, y0, x1, y0);
	draw_line(env, x0, y1, x1, y1);
	draw_line(env, x1, y0, x1, y1);
}

void	draw_grid(t_env *env)
{
	long	i;
	long	j;
	// long	scale;
	// long	transx;
	// long	transy;

	i = 0;
	j = 0;
	printf("Min width: %ld Min height: %ld\n", env->width, env->height);

	// scale = env->width > env->height ? (WIN_HEIGHT / 2) / (env->height - 1) : (WIN_WIDTH/ 2) / (env->width - 1);
	// transx = (WIN_WIDTH - ((env->width - 1) * scale)) / 2;
	// transy = (WIN_HEIGHT - ((env->height - 1) * scale)) / 2;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			if (j < env->width - 1)
				draw_line(env, env->pnts[i][j].x, env->pnts[i][j].y, env->pnts[i][j + 1].x, env->pnts[i][j + 1].y);
			if (i < env->height - 1)
				draw_line(env, env->pnts[i][j].x,env->pnts[i][j].y,env->pnts[i + 1][j].x, env->pnts[i + 1][j].y);
			j++;
		}
		i++;
	}
}

void	draw_fill(t_env *env)
{
	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 800; j++)
		{
			mlx_pixel_put(env->mlx, env->window, i, j, 0x33aa55);
		}
	}
}