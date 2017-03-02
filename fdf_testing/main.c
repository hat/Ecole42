/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
}

int		fdf_get_error(int error, char *string)
{
	ft_printf("%s\n", string);
	return (error);
}

int		get_expose(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
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
		mlx_pixel_put(env->mlx, env->window, x, y, 0x002200);
	}
	return (0);
}

int		key_manager(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_SPACE)
		mlx_clear_window(env->mlx, env->window);
	env->move_y = (keycode == KEY_UP) ? env->move_y - 5 : env->move_y;
	env->move_y = (keycode == KEY_DOWN) ? env->move_y + 5 : env->move_y;
	env->move_x = (keycode == KEY_RIGHT) ? env->move_x + 5 : env->move_x;
	env->move_x = (keycode == KEY_LEFT) ? env->move_x - 5 : env->move_x;
	env->color = (keycode == KEY_Z) ? env->color - 200 : env->color;
	env->color = (keycode == KEY_X) ? env->color + 200 : env->color;
	draw(env);
	return (0);
}

void	run_graphics(t_env *env)
{
	draw(env);
	mlx_key_hook(env->window, key_manager, env);
	mlx_mouse_hook(env->window, mouse_manager, env);
	//mlx_expose_hook(env->window, get_expose, env);
	//mlx_loop(env->mlx);
	mlx_loop(env->mlx);
}

int		main(int argc, char *argv[])
{
	t_env	*env;
	int fd;

	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_printf("error: Unable to open file");
		env = (t_env *)ft_memalloc(sizeof(t_env));
		env->mlx = mlx_init();
		env->window = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		env->color = COLOR;
		parse_map(env, fd);
		get_coordinates(env);
		isometric(env);
		run_graphics(env);
		free(env);
	}
	else
		return (fdf_get_error(1, "USAGE: ./fdf {filename}"));
	return (0);
}
