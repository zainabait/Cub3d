/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:37:23 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/21 18:21:51 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*ft_itoa(int n)
{
	char	arr[12];
	long	b;
	int		i;
	int		divisor;

	b = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (b < 0)
		b *= -1;
	divisor = 1000000000;
	arr[0] = '0';
	i = 0;
	while (++i <= 10)
	{
		arr[i] = b / divisor + '0';
		b %= divisor;
		divisor /= 10;
	}
	i = 0;
	while (arr[i] == '0')
		i++;
	if (n < 0)
		arr[--i] = '-';
	return (arr[11] = '\0', ft_strdup(&arr[i]));
}

void	load_sprite_textures(t_cube *cube)
{
	char	*str;
	char	*tmp2;
	int		i;

	i = 0;
	while (i < 100)
	{
		str = NULL;
		str = ft_strjoin(str, "knif/");
		tmp2 = ft_itoa(i + 1);
		str = ft_strjoin(str, tmp2);
		str = ft_strjoin(str, ".png");
		cube->data->s_sprite[i] = mlx_load_png(str);
		if (!cube->data->s_sprite[i])
			ft_error_message("Error: sprite texture encountered");
		i++;
	}
}

void	ft_animation(t_cube *cub)
{
	static int	i;

	if (i % 6 == 0)
	{
		mlx_delete_image(cub->mlx, cub->data->tp);
		cub->data->tp = mlx_texture_to_image(cub->mlx, cub->data->s_sprite[cub->data->fram]);
		mlx_image_to_window(cub->mlx, cub->data->tp, 0,0);
		if (!cub->data->animation_loading)
			cub->data->fram = 0;
		if (cub->data->animation_loading && cub->data->fram == 99)
		{
			cub->data->fram = 0;
			cub->data->animation_loading = 0;
		}
		cub->data->fram++;
	}
	i++;
}

