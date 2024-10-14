/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:10 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 22:04:51 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	function(void *param)
{
	t_cube *cube = param;
	
	if (cube->image)
		mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	render_3d(cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}

void load_textures(t_cube *cube)
{
	cube->data->no_texture = mlx_load_png(cube->data->no);
	if (!cube->data->no_texture)
		ft_error_message("Error\nNo texture");	
	cube->data->so_texture = mlx_load_png(cube->data->so);
	if (!cube->data->so_texture)
		ft_error_message("Error\nSo texture");
	cube->data->we_texture = mlx_load_png(cube->data->we);
	if (!cube->data->we_texture)
		ft_error_message("Error\nWe texture");
	cube->data->ea_texture = mlx_load_png(cube->data->ea);
	if (!cube->data->ea_texture)
		ft_error_message("Error\nEa texture");
	cube->data->no_image_texture = mlx_texture_to_image(cube->mlx, cube->data->no_texture);
	if (!cube->data->no_image_texture)
		ft_error_message("Error\nEa texture");
	// cube->data->so_image_texture = mlx_texture_to_image(cube->mlx, cube->data->so_texture);
	// if (!cube->data->so_image_texture)
	// 	ft_error_message("Error\nEa texture");
	// cube->data->we_image_texture = mlx_texture_to_image(cube->mlx, cube->data->we_texture);
	// if (!cube->data->we_image_texture)
	// 	ft_error_message("Error\nEa texture");
	// cube->data->ea_image_texture = mlx_texture_to_image(cube->mlx, cube->data->ea_texture);
	// if (!cube->data->ea_image_texture)
	// 	ft_error_message("Error\nEa texture");
}

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
	cube->player->angle = -1 * M_PI / 2;
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
	load_textures(cube);
	initialize_position(cube->data, &player->x, &player->y);
	mlx_loop_hook(cube->mlx, function, cube);
	mlx_key_hook(cube->mlx, handle_key_input, cube);
	mlx_loop(cube->mlx);
}
