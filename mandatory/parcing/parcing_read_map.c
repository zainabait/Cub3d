/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_read_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:58:30 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/05 12:01:43 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_file_isvalid(char *file)
{
	char	*tmp;

	tmp = file + ft_strlen(file) - 4;
	if (ft_strcmp(tmp, ".cub"))
		ft_error_message("Error : Invalid extension!!");
}

int	lines_lenght(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		line = get_next_line(fd);
	}
	return (count);
}

void	rep_newline(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '\n')
			line[j] = '\0';
		j++;
	}
}

char	**get_map(char *file, int count)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	1 && (i = 0, map = NULL);
	fd = open(file, O_RDWR);
	if (fd < 0)
		ft_error_message("Error: from fd!");
	map = (char **)talloc(sizeof(char *) * (count + 1));
	if (!map)
		ft_error_message("Error: from talloc!");
	line = get_next_line(fd);
	while (line)
	{
		rep_newline(line);
		map[i] = ft_strdup(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**ft_read_map(char *file)
{
	int		fd;
	int		count;
	char	**map;

	1 && (count = 0, map = NULL);
	fd = open(file, O_RDWR);
	if (fd < 0)
		ft_error_message("Error: from fd!");
	count = lines_lenght(fd);
	close(fd);
	map = get_map(file, count);
	if (!map)
		ft_error_message("Error: from get_map!");
	return (map);
}
