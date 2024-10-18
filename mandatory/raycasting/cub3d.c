/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:10 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/18 14:59:09 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	function(void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	if (cube->image)
		mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	render_3d(cube);
	move_player(cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}

int	mlx_data_init(t_cube *cube)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (!cube->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (cube->image)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int	data_init(t_cube *cube, t_player *player, t_inter *hit, t_ray *ray)
{
	cube->hit = hit;
	cube->ray = ray;
	cube->player = player;
	cube->player->angle = -1 * M_PI / 2;
	if (mlx_data_init(cube))
		return (1);
	return (0);
}

void	mouse_func(double xpos, double ypos, void *param)
{
	t_cube	*cub;

	(void)ypos;
	cub = (t_cube *)param;
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	if (cub->cursor_hidden && cub->player->prev_x > xpos)
		cub->player->angle -= fabs(cub->player->prev_x - xpos) * 0.004;
	else if (cub->cursor_hidden && cub->player->prev_x < xpos)
		cub->player->angle += fabs(cub->player->prev_x - xpos) * 0.004;
	cub->player->prev_x = xpos;
}

int	main(int ac, char **av)
{
	t_cube		*cube;
	t_player	player;
	t_inter		hit;
	t_ray		ray[SCREEN_WIDTH];

	if (ac != 2)
		ft_error_message("num of args isn't correct.Usage: ./cub3D <map_file>");
	cube = talloc(sizeof(t_cube));
	cube->data = ft_parsing(av);
	if (data_init(cube, &player, &hit, ray))
		return (1);
	cube->cursor_hidden = 0;
	load_textures(cube);
	initialize_position(cube->data, &cube->player->x, &cube->player->y);
	mlx_loop_hook(cube->mlx, function, cube);
	mlx_cursor_hook(cube->mlx, mouse_func, cube);
	mlx_key_hook(cube->mlx, handle_key_input, cube);
	mlx_loop(cube->mlx);
}
