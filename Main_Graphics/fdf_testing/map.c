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

void	rot_z_axis(t_point *point, float angle)
{
	float	temp;

	temp = point->x;
	point->x = (point->x * cos(angle) + (point->y * sin(angle)));
	point->y = (temp * -sin(angle) + (point->y * cos(angle)));
}

void	rot_x_axis(t_point *point, float angle)
{
	float	temp;

	temp = point->y;
	point->y = (point->y * cos(angle) + (point->z * sin(angle)));
	point->z = (temp * -sin(angle) + (point->z * cos(angle)));
}

void	isometric(t_env *env)
{
	env->trans.scale = ceil((env->wdth > env->hght) ? (WIN_HEIGHT / 2)
	/ ((float)env->hght - 1) : (WIN_WIDTH / 2) / ((float)env->wdth - 1));
	env->trans.transx = (WIN_WIDTH - (env->wdth - 1) * env->trans.scale) / 2;
	env->trans.transy = (WIN_HEIGHT - (env->hght - 1) * env->trans.scale) / 2;
	env->crds->x = 0;
	while (env->crds->x < env->hght)
	{
		env->crds->y = 0;
		while (env->crds->y < env->wdth)
		{
			env->pnts[env->crds->x][env->crds->y].x *= env->trans.scale;
			env->pnts[env->crds->x][env->crds->y].y *= env->trans.scale;
			env->pnts[env->crds->x][env->crds->y].z *= env->trans.scale;
			env->pnts[env->crds->x][env->crds->y].x -= env->trans.transx;
			env->pnts[env->crds->x][env->crds->y].y -= env->trans.transy;
			rot_z_axis(&env->pnts[env->crds->x][env->crds->y],
				45 * (M_PI / 180));
			rot_x_axis(&env->pnts[env->crds->x][env->crds->y],
				atan(-sqrt(2)));
			env->pnts[env->crds->x][env->crds->y].x += (WIN_HEIGHT / 2);
			env->pnts[env->crds->x][env->crds->y].y += (WIN_WIDTH / 2);
			env->crds->y++;
		}
		env->crds->x++;
	}
}

int		setup_crds_pnts(t_env *env)
{
	if (!(env->crds = (t_coords *)ft_memalloc(sizeof(t_coords))))
		return (fdf_get_error(1, "ERROR: malloc failed"));
	if (!(env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->hght)))
		return (fdf_get_error(1, "ERROR: malloc failed"));
	return (0);
}

int		get_coordinates(t_env *env)
{
	setup_crds_pnts(env);
	while (env->crds->y < env->hght)
	{
		env->crds->x = 0;
		if (!(env->pnts[env->crds->y] =
				(t_point *)ft_memalloc(sizeof(t_point) * env->wdth)))
			return (fdf_get_error(1, "ERROR: malloc failed"));
		while (env->crds->x < env->wdth)
		{
			env->pnts[env->crds->y][env->crds->x].x = env->crds->x;
			env->pnts[env->crds->y][env->crds->x].y = env->crds->y;
			env->pnts[env->crds->y][env->crds->x].z =
				atoi(env->pnts_read[env->crds->i]);
			env->pnts[env->crds->y][env->crds->x].height =
			env->pnts[env->crds->y][env->crds->x].z;
			env->z_min = (env->z_min > env->pnts[env->crds->y][env->crds->x].z)
			? env->pnts[env->crds->y][env->crds->x].z : env->z_min;
			env->z_max = (env->z_max < env->pnts[env->crds->y][env->crds->x].z)
			? env->pnts[env->crds->y][env->crds->x].z : env->z_max;
			env->crds->x++;
			env->crds->i++;
		}
		env->crds->y++;
	}
	return (0);
}
