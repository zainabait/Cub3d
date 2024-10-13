/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:09:37 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 16:01:43 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"

# define FOV_ANGLE (60 * (M_PI / 180))
# define TILE_SIZE 50
# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720
# define SPEED 5

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct intersection
{
    double x;
    double y;
    double dist;
    bool    ver_hit;
}    t_inter;

typedef struct player
{
    double x;
    double y;
    double    angle;
}    t_player;

// ***************************

typedef struct s_heap            t_heap;

struct s_heap
{
    void    *ptr;
    t_heap    *next;
};

// ***************************

typedef struct s_data
{
    t_heap    *heap;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    **map;
    int        f_c;
    int        c_color;
    int        height;
    size_t    width;
}            t_data;

// ***************************

typedef struct cube
{
    mlx_t*            mlx;
    mlx_image_t*    image;
    t_player        *player;
    t_inter         *hit;
	t_data			*data;
}    t_cube;

// ***************************


char    *ft_strjoin(char *s1, char *s2);
char    *ft_substr(const char *s, unsigned int start, size_t len);
size_t    ft_strlen(const char *str);
char    *ft_strdup(const char *src);
char    *get_next_line(int fd);
char    **ft_split(char const *s, char c);
void    ft_error_message(char *mess);
void    check_file_isvalid(char *file);
char    **ft_read_map(char *file);
int        ft_strcmp(const char *s1, const char *s2);
char    *ft_strtrim(const char *s1, const char *set);
void    ft_free_leak(char **str);
int        ft_atoi(const char *str);
int        ft_strncmp(const char *s1, const char *s2, size_t n);
/*______________________ parsing map_____________*/

void    get_data(t_data *args, char **file, int *r);
char    *check_last_line(char **file);
char    **get_map_filled_with_spaces(char **file, t_data *args);
int        check_line_is_empty(char *line);
void    check_first_line(char *line);
void    check_map(char **file, t_data *args);
void    init_data(t_data *args);
void    check_params(t_data args);
void    check_elements(t_data *args);
void    assign_color(t_data *args, char *line, char **tmp2);
void    is_num(char *str);
void    check_map_round_byones(t_data *args);
void    ivalid_lelement(char *str);
void    rep_spaseses_to_ones(t_data *args);
t_data     *ft_parsing(char **av);

/*-----------garbege collecter---------------*/
t_data    *get_cub(t_data *cub);
void    clearheap(t_heap **node);
void    *talloc(size_t __size);

/*-----------raycasting---------------*/
void	render_3d(void *param);
void	handle_key_input(mlx_key_data_t keydata, void* param);
t_inter	find_vertical_intersection(t_cube *cube, double angle);
t_inter	find_horizontal_intersection(t_cube *cube, double angle);
void	initialize_position(t_data *data, double *x, double *y);
bool	is_wall(int x, int y, t_cube *cub);
void	render_wall(t_cube *cube, double x, double ray);
void render_minimap(void* param);
void bresenham_line(long from_x, long from_y, long to_x, long to_y, t_cube *cub, uint32_t color);
int	get_sign(int a, int b);
void	calculate_closest_ray(t_inter ch, t_inter cv, t_cube *cube);
void	draw_player(void *param);
void	put_pixel_safe(mlx_image_t *img, long x, long y, long color);


#endif