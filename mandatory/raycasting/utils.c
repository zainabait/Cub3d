/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:29 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/14 21:54:20 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

bool	is_wall(size_t x, int y, t_cube *cub)
{
	(void)cub;
	if (x < 0 || x > cub->data->width * TILE_SIZE || y < 0 || y > cub->data->height * TILE_SIZE)
		return (1);
	if (cub->data->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}
