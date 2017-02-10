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
	printf("Drawing circle....");
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
	printf("Circle drawn!\n");
}

void	draw_line(t_env *env, int x0, int y0, int x1, int y1)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;

	while (1)
	{
		mlx_pixel_put(env->mlx, env->window, x0, y0, COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
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
	long	ind;
	long	scale;

	ind = 0;
	scale = WIN_HEIGHT / env->height;
	while (ind < env->height * env->width - 1)
	{
		if (env->pnts[ind].x * scale == env->pnts[ind + 1].x * scale)
		{
			printf("Drawing line from [%ld, %ld] to [%ld, %ld]\n", env->pnts[ind].x * scale, env->pnts[ind].y * scale, env->pnts[ind + 1].x * scale, env->pnts[ind + 1].y * scale);
			printf("Color is: %ld\n", env->pnts[ind].z);
			draw_line(env, env->pnts[ind].x * scale, env->pnts[ind].y * scale, env->pnts[ind + 1].x * scale, env->pnts[ind + 1].y * scale);
		}
		ind++;
	}
	ind = 0;
	while (ind < env->height * env->width - 1)
	{
		if (env->pnts[ind].x * scale == env->pnts[ind + 1].x * scale)
		{
			draw_box(env, env->pnts[ind].y * scale, env->pnts[ind].x * scale, env->pnts[ind + 1].y * scale, env->pnts[ind + 1].x * scale);
			draw_box(env, env->pnts[ind].x * scale, env->pnts[ind].y * scale, env->pnts[ind + 1].x * scale, env->pnts[ind + 1].y * scale);
		}
		ind++;
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