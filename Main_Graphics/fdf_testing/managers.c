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

void	setup_point_height(t_env *env, t_point *pnt, int i, int j)
{
	pnt[0].x = env->pnts[i][j].x;
	pnt[0].y = env->pnts[i][j].y;
	pnt[1].x = env->pnts[i + 1][j].x;
	pnt[1].y = env->pnts[i + 1][j].y;
}

void	setup_point_width(t_env *env, t_point *pnt, int i, int j)
{
	pnt[0].x = env->pnts[i][j].x;
	pnt[0].y = env->pnts[i][j].y;
	pnt[1].x = env->pnts[i][j + 1].x;
	pnt[1].y = env->pnts[i][j + 1].y;
}

int		get_expose(t_env *env)
{
	mlx_clear_window(env->mlx, env->win);
	draw(env);
	return (0);
}

int		mouse_manager(int button, int x, int y, t_env *env)
{
	if (button >= 1)
	{
		draw_circle(env, x + 20, y, 20);
		draw_circle(env, x, y + 20, 20);
		draw_circle(env, x - 20, y, 20);
		draw_circle(env, x, y - 20, 20);
		mlx_pixel_put(env->mlx, env->win, x, y, 0x002200);
	}
	return (0);
}

int		key_manager(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_SPACE)
		mlx_clear_window(env->mlx, env->win);
	env->move_y = (keycode == KEY_UP) ? env->move_y - 5 : env->move_y;
	env->move_y = (keycode == KEY_DOWN) ? env->move_y + 5 : env->move_y;
	env->move_x = (keycode == KEY_RIGHT) ? env->move_x + 5 : env->move_x;
	env->move_x = (keycode == KEY_LEFT) ? env->move_x - 5 : env->move_x;
	env->clr1 = (keycode == KEY_Z) ? env->clr1 - 200 : env->clr1;
	env->clr1 = (keycode == KEY_X) ? env->clr1 + 200 : env->clr1;
	env->clr2 = (keycode == KEY_C) ? env->clr2 - 200 : env->clr2;
	env->clr2 = (keycode == KEY_V) ? env->clr2 + 200 : env->clr2;
	setup_colors(env);
	draw(env);
	return (0);
}
