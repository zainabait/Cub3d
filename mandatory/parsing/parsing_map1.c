/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:19:13 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/13 12:27:47 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	first_last_char(t_data *args)
{
	int	i;
	int	j;

	i = 0;
	if (args->map[i])
		i++;
	while (args->map[i])
	{
		j = 1;
		if (args->map[i][0] == '0' \
			||args->map[i][ft_strlen(args->map[i]) - 1] == '0')
			ft_error_message("Error: Invalid map!!");
		while (args->map[i][j])
		{
			if (args->map[i][j] == '0')
			{
				if (args->map[i][j - 1] == ' ' || args->map[i][j + 1] == ' ' \
	|| args->map[i - 1][j] == ' ' || args->map[i + 1][j] == ' ')
					ft_error_message("Error: Invalid map!!");
			}
			j++;
		}
		i++;
	}
}

int	check_line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*check_last_line(char **file)
{
	int	i;

	i = 0;
	while (file[i] && !check_line_is_empty(file[i]))
		i++;
	if ((!file[i] && i != 0) \
		|| (file[i] && check_line_is_empty(file[i])))
		return (file[i - 1]);
	return (file[i]);
}

static void	check_empty_line_inside_map(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (check_line_is_empty(file[i]))
		{
			while (file[i] && check_line_is_empty(file[i]))
				i++;
			if (file[i])
				ft_error_message("Error: Invalid map!!");
		}
		if (file[i])
			i++;
	}
}

void	check_map(char **file, t_data *args)
{
	int	i;
	int	j;

	1 && (i = 0, j = 0);
	while (file[i] && check_line_is_empty(file[i]))
		i++;
	if (!file[i])
		ft_error_message("Error: Invalid map!!");
	check_empty_line_inside_map(file + i);
	check_first_line(file[i]);
	check_first_line(check_last_line(file + i));
	args->map = get_map_filled_with_spaces(file + i, args);
	first_last_char(args);
}
