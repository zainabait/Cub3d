/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:40:44 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/11 18:37:32 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	check_first_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			ft_error_message("Error: Invalid map!!");
		i++;
	}
}

size_t	get_longest_line(char **file)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(file[i]);
	while (file[i])
	{
		if (ft_strlen(file[i]) > size)
			size = ft_strlen(file[i]);
		i++;
	}
	return (size);
}

int	get_size_of_map(char **file)
{
	int	i;

	i = 0;
	while (file[i] && !check_line_is_empty(file[i]))
		i++;
	return (i);
}

char	*char_of_spaces(int len)
{
	char	*str;
	int		i;

	i = 0;
	str = talloc(len + 1);
	if (!str)
		ft_error_message("Error: from talloc!!");
	while (i < len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**get_map_filled_with_spaces(char **file, t_data *args)
{
	char	**map;
	char	*spaces;
	int		i;

	1 && (i = 0, map = NULL);
	args->width = get_longest_line(file);
	args->height = get_size_of_map(file);
	map = talloc(sizeof(char *) * (args->height + 1));
	if (!map)
		ft_error_message("Error: from talloc!!");
	while (i < args->height)
	{
		spaces = char_of_spaces(args->width - ft_strlen(file[i]));
		if (ft_strlen(file[i]) < args->width)
			map[i] = ft_strjoin(file[i], spaces);
		else
			map[i] = ft_strdup(file[i]);
		i++;
	}
	return (map[i] = NULL, map);
}