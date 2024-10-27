/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:31:42 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/27 18:18:16 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	function(void *param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	ft_close_door(cube);
	ft_clear_image(cube->image);
	move_player(cube);
	render_3d(cube);
	ft_animation(cube);
}

int	main(int ac, char **av)
{
	t_cube		cube;
	t_player	player;
	t_inter		hit;
	t_ray		ray[SCREEN_WIDTH];

	if (ac != 2)
		ft_error_message("num of args isn't correct.Usage: ./cub3D <map_file>");
	get_cub(&cube);
	cube.data = ft_parsing(av);
	if (data_init(&cube, &player, &hit, ray))
		return (1);
	cube.cursor_hidden = 0;
	load_textures(&cube);
	initialize_position(cube.data, &cube.player->x, &cube.player->y);
	load_sprite_textures(&cube);
	cube.data->fram = 0;
	mlx_loop_hook(cube.mlx, function, &cube);
	mlx_cursor_hook(cube.mlx, ft_mouse, &cube);
	mlx_key_hook(cube.mlx, handle_key_input, &cube);
	mlx_loop(cube.mlx);
}
