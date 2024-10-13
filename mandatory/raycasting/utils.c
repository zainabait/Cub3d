/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:29 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 13:26:06 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

bool	is_wall(int x, int y, t_cube *cub)
{
	(void)cub;
	if (x < 0 || x > 14 * TILE_SIZE || y < 0 || y > 10 * TILE_SIZE)
		return (1);
	if (map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}
