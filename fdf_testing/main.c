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
	draw_grid(env);
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
	{
		mlx_destroy_window(env->mlx, env->window);
		exit(1);
	}
	if (keycode == KEY_W)
	{
		env->trans.scale++;
		isometric(env);
		mlx_clear_window(env->mlx, env->window);
		draw(env);
	}
	if (keycode == KEY_SPACE)
	{
		mlx_clear_window(env->mlx, env->window);
		draw(env);
	}
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
