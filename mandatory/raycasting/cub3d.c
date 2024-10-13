/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:10 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 15:54:20 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	main(int ac, char **av)
{
	t_cube		*cube;
	t_player	*player;
	t_inter		hit;

	if (ac != 2)
		ft_error_message("num of args isn't correct.Usage: ./cub3D <map_file>");
	cube = malloc(sizeof(t_cube));
	player = malloc(sizeof(t_player));
	cube->data = ft_parsing(av);
	cube->hit = &hit;
	cube->player = player;
	cube->player->angle = 0;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (!(cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	initialize_position(cube->data, &player->x, &player->y);
	mlx_loop_hook(cube->mlx, render_3d, cube);
	mlx_key_hook(cube->mlx, handle_key_input, cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_loop(cube->mlx);
}
