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

void	draw(t_env *env)
{
	int bpp;
	int ed;
	
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->pix_map = mlx_get_data_addr(env->img, &bpp, &(env->lsize), &ed);
	draw_grid(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
}

void	setup_colors(t_env *env)
{
	int		i;
	double	r[3];
	double	g[3];
	double	b[3];

	env->clrs = (int *)malloc(sizeof(int) * 101);
	r[0] = (double)(env->clr1 >> 16 & 0xFF);
	r[1] = (double)(env->clr2 >> 16 & 0xFF);
	g[0] = (double)(env->clr1 >> 8 & 0xFF);
	g[1] = (double)(env->clr2 >> 8 & 0xFF);
	b[0] = (double)(env->clr1 & 0xFF);
	b[1] = (double)(env->clr2 & 0xFF);
	i = -1;
	while (++i <= 100)
	{
		r[2] = (double)(r[1] * i) / 100 + (double)(r[0] * (100 - i)) / 100;
		g[2] = (double)(g[1] * i) / 100 + (double)(g[0] * (100 - i)) / 100;
		b[2] = (double)(b[1] * i) / 100 + (double)(b[0] * (100 - i)) / 100;
		env->clrs[i] = (int)r[2] << 16 | (int)g[2] << 8 | (int)b[2];
	}
}

void	draw_point(t_env *env, int x, int y)
{
	int				i;
	int				which;
	unsigned int	color;

	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		which = ((float)env->cur_z - (float)env->z_min) / ((float)env->z_max - (float)env->z_min) * 100;
		color = env->clrs[(int)which];
		i = (x * 4) + (y * env->lsize);
		env->pix_map[i] = color;
		env->pix_map[++i] = color >> 8;
		env->pix_map[++i] = color >> 16;
	}
}

void	draw_line(t_env *env, t_point *pnt)
{
	env->line.dx = abs(pnt[1].x - pnt[0].x);
	env->line.sx = pnt[0].x < pnt[1].x ? 1 : -1;
	env->line.dy = abs(pnt[1].y - pnt[0].y);
	env->line.sy = pnt[0].y < pnt[1].y ? 1 : -1;
	env->line.err = (env->line.dx > env->line.dy ?
		env->line.dx : -env->line.dy) / 2;
	while (1)
	{
		draw_point(env, pnt[0].x + env->move_x, pnt[0].y + env->move_y);
		if (pnt[0].x == pnt[1].x && pnt[0].y == pnt[1].y)
			break ;
		env->line.e2 = env->line.err;
		if (env->line.e2 > -env->line.dx)
		{
			env->line.err -= env->line.dy;
			pnt[0].x += env->line.sx;
		}
		if (env->line.e2 < env->line.dy)
		{
			env->line.err += env->line.dx;
			pnt[0].y += env->line.sy;
		}
	}
}

void	draw_grid(t_env *env)
{
	long	i;
	long	j;
	t_point	*pnt;

	i = -1;
	pnt = (t_point *)ft_memalloc(sizeof(t_point) * 2);
	while (++i < env->hght)
	{
		j = -1;
		while (++j < env->wdth)
		{
			env->cur_z = env->pnts[i][j].height;
			if (j < env->wdth - 1)
			{
				setup_point_width(env, pnt, i, j);
				draw_line(env, pnt);
			}
			if (i < env->hght - 1)
			{
				setup_point_height(env, pnt, i, j);
				draw_line(env, pnt);
			}
		}
	}
	ft_memdel((void *)&pnt);
}
