/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:24 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/11 16:39:53 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include "MLX42.h"

# define FOV_ANGLE (60 * (M_PI / 180))
# define TILE_SIZE 50
# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720

typedef struct intex
{
	double x;
	double y;
	double dist;
	bool	ver_hit;
}	t_intex;

typedef struct player
{
	double x;
	double y;
	double	angle;
}	t_player;

typedef struct cube
{
	mlx_t*			mlx;
	mlx_image_t*	image;
	t_player		*player;
	t_intex			*hit;
}	t_cube;
