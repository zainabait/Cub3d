/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:26:15 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/08 16:27:20 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main( int ac, char **av)
{
	t_data	args;
	char	**file;
	int		i;

	get_cub(&args);
	1 && (i = 0, args.heap = NULL);
	if (ac != 2)
		ft_error_message("Error : Invalid number of arguments!!");
	check_file_isvalid(av[1]);
	file = ft_read_map(av[1]);
	if (!file[0])
		ft_error_message("Error: empty map!!");
	init_data(&args);
	get_data(&args, file, &i);
	check_params(args);
	check_map(file + i, &args);
	check_map_round_byones(&args);
	check_elements(&args);
	clearheap(&args.heap);
	return (0);
}
