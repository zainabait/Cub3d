/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:05:27 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/18 12:33:25 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	apply_shadow(uint32_t *color, t_cube *cube, double max_distance)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	double		intensity;

	intensity = 1 - (cube->ray->dis / max_distance);
	if (intensity < 0.3)
		intensity = 0.3;
	r = (*color >> 24) & 0xFF;
	g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	*color = (r << 24) | (g << 16) | (b << 8) | 0xff;
}

void	cal_wall_dimen(t_cube *cube, int *from_y, int *to_y, double *w_height)
{
	double	base_distance;

	base_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	*w_height = (TILE_SIZE / cube->ray->dis) * base_distance;
	*from_y = (SCREEN_HEIGHT / 2) - (*w_height / 2);
	*to_y = *from_y + *w_height;
	if (*from_y < 0)
		*from_y = 0;
	if (*to_y > SCREEN_HEIGHT)
		*to_y = SCREEN_HEIGHT;
}

void	ft_texture_to_image(t_cube *cube)
{
	cube->data->no_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->no_texture);
	if (!cube->data->no_image_texture)
		ft_error_message("Error: 'No' texture encountered");
	cube->data->so_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->so_texture);
	if (!cube->data->so_image_texture)
		ft_error_message("Error: 'So' texture encountered");
	cube->data->we_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->we_texture);
	if (!cube->data->we_image_texture)
		ft_error_message("Error: 'We' texture encountered");
	cube->data->ea_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->ea_texture);
	if (!cube->data->ea_image_texture)
		ft_error_message("Error: 'Ea' texture encountered");
}
