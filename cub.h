/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:38:11 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/05 12:15:22 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "mlx.h"
# include <limits.h>
# include <unistd.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// ***************************
typedef struct s_heap			t_heap;

struct s_heap
{
	void	*ptr;
	t_heap	*next;
};

// ***************************
typedef struct s_data
{
	t_heap	*heap;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int		f_c;
	int		c_color;
	int		height;
	size_t	width;
}			t_data;

char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
void	ft_error_message(char *mess);
void	check_file_isvalid(char *file);
char	**ft_read_map(char *file);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
void	ft_free_leak(char **str);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*________________________________________ parcing map_____________*/

void	get_data(t_data *args, char **file, int *r);
char	*check_last_line(char **file);
char	**get_map_filled_with_spaces(char **file, t_data *args);
int		check_line_is_empty(char *line);
void	check_first_line(char *line);
void	check_map(char **file, t_data *args);
void	init_data(t_data *args);
void	check_params(t_data args);
void	check_elements(t_data *args);
void	assign_color(t_data *args, char *line, char **tmp2);
void	is_num(char *str);
void	check_map_round_byones(t_data *args);

/*-----------garbege collecter---------------*/
t_data	*get_cub(t_data *cub);
void	clearheap(t_heap **node);
void	*talloc(size_t __size);

#endif