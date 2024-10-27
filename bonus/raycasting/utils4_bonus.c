/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:17:24 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/27 18:25:12 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	open_door(t_cube *cube)
{
	int		j;
	size_t	i;
	double	dist_x;
	double	dist_y;
	double	dist;

	j = 0;
	while (j < cube->data->height)
	{
		i = 0;
		while (i < cube->data->width)
		{
			if (cube->data->map[j][i] == 'D')
			{
				dist_x = i * TILE_SIZE + TILE_SIZE / 2 - cube->player->x;
				dist_y = j * TILE_SIZE + TILE_SIZE / 2 - cube->player->y;
				dist = sqrt(dist_x * dist_x + dist_y * dist_y);
				if (dist < TILE_SIZE * 3)
					cube->data->map[j][i] = 'd';
			}
			i++;
		}
		j++;
	}
}

void	ft_close_door(t_cube *cube)
{
	int		j;
	size_t	i;
	double	dist_x;
	double	dist_y;
	double	dist;

	j = 0;
	while (j < cube->data->height)
	{
		i = 0;
		while (i < cube->data->width)
		{
			if (cube->data->map[j][i] == 'd')
			{
				dist_x = i * TILE_SIZE + TILE_SIZE / 2 - cube->player->x;
				dist_y = j * TILE_SIZE + TILE_SIZE / 2 - cube->player->y;
				dist = sqrt(dist_x * dist_x + dist_y * dist_y);
				if (dist > TILE_SIZE * 4)
					cube->data->map[j][i] = 'D';
			}
			i++;
		}
		j++;
	}
}
