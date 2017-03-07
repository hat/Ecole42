/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:02:16 by thendric          #+#    #+#             */
/*   Updated: 2017/02/03 11:02:17 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 900

# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			height;
}				t_point;

typedef struct	s_line
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
}				t_line;

typedef struct	s_circle
{
	int			y;
	int			err;
}				t_circle;

typedef struct	s_trans
{
	float		scale;
	int			transx;
	int			transy;
}				t_trans;

typedef struct	s_coords
{
	int			x;
	int			y;
	int			i;
	int			cur_pnt;
}				t_coords;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pix_map;
	char		**pnts_read;
	int			hght;
	int			wdth;
	int			*clrs;
	int			clr1;
	int			clr2;
	int			lsize;
	double		move_y;
	double		move_x;
	int			z_min;
	int			z_max;
	int			cur_z;
	t_coords	*crds;
	t_trans		trans;
	t_point		**pnts;
	t_point		**z;
	t_line		line;
	t_circle	crcl;
}				t_env;

# define COLOR 0xEBF3DE

/*
** Draw functions
*/
void			draw(t_env *env);
void			isometric(t_env *env);
void			draw_circle(t_env *env, int x0, int y0, int x);
void			draw_box(t_env *env, int x0, int y0, int x1, int y1);
void			draw_grid(t_env *env);
void			draw_fill(t_env *env);
void			setup_colors(t_env *env);
void			setup_point_width(t_env *env, t_point *pnt, int i, int j);
void			setup_point_height(t_env *env, t_point *pnt, int i, int j);

/*
** Map functions
*/
int				get_coordinates(t_env *env);
int				get_map_width(t_env *env, int counter);
void			parse_map(t_env *env, int fd);

/*
** Helper functions
*/
int				mouse_manager(int button, int x, int y, t_env *env);
int				fdf_get_error(int error, char *string);
int				key_manager(int keycode, t_env *env);
int				get_expose(t_env *env);

#endif
