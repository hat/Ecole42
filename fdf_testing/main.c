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

#include "fdf.h"

void	draw(t_env *env)
{
	//draw_fill(env);
	//printf("Fill drawn!\n");
	//draw_circle(env, 100, 100, 150);
	//printf("Circle drawn!\n");
	//draw_line(env, 0, 0, 200, 500);
	//printf("Line drawn!\n");
	//draw_box(env, 50, 50, 300, 300);
	//printf("Box drawn!\n");
	//draw_fill(env);
	draw_grid(env);
	printf("Grid drawn!\n");
}

int		fdf_get_error(int error, char *string)
{
	ft_printf("%s\n", string);
	return (error);
}

int		get_expose(t_env *env)
{
	draw(env);
	return (0);
}

void	reset_window(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	get_expose(env);
}

int		mouse_manager(int button, int x, int y, t_env *env)
{
	printf("Button:%d X:%d Y:%d\n", button, x, y);
	draw_box(env, x, y, x + 10, y + 10);
	draw_circle(env, x, y, 20);
	mlx_pixel_put(env->mlx, env->window, x, y, 0x002200);
	return (0);
}

int		key_manager(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(env->mlx, env->window);
		exit (1); //Exits program executable
	}
	if (keycode == KEY_SPACE)
	{
		reset_window(env);
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
	mlx_loop(env->mlx);
}

int		main(int argc, char *argv[])
{
	t_env	*env;

	if (argc > 1)
	{
		env = (t_env *)ft_memalloc(sizeof(t_env));
		env->mlx = mlx_init();
		env->window = mlx_new_window(env->mlx, WIN_HEIGHT, WIN_WIDTH, "Playground");
		get_map_size(env, argv);
		get_coordinates(env);
		run_graphics(env);
		free(env);
	}
	return (0);
}
