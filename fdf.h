/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:14:56 by abchan            #+#    #+#             */
/*   Updated: 2018/05/11 14:16:36 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WNDW_HGHT 1000
# define WNDW_WDTH 2000
# define ESCKEY 53
# define WKEY 13
# define AKEY 0
# define SKEY 1
# define DKEY 2
# define ONEKEY 18
# define TWOKEY 19
# define RKEY 15
# define FKEY 3
# define QKEY 12
# define EKEY 14
# define PKEY 35
# define PLUS 24
# define MINUS 27
# define SPACKEY 49
# define TRANSLAT_AMT 10
# define SCALE_AMT 2
# define DISTANCE 50
# include "jfj.h" // delete later
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct	s_cords
{
	float	x;
	float	y;
	float	z;
	float	homocord;
	float	px;
	float	py;
	float	pz;
}				t_cords;

typedef struct s_img
{
	void	*ptr;
	char	*data_addr;
	int		bbp;
	int		line_size;
	int		endian;
}				t_img;
typedef struct	s_map
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_cords	*mapcords;
	int		xtrans;
	int		ytrans;
	int		scale;
	int		rotatez;
	int		rotatex;
	int		rotatey;
	int		perspective;
	int 	pointcount;
	int		mapwidth;
	int		mapheight;
	int		maxmapdepth;
	int		minmapdepth;
	int		color;
}				t_map;

t_map		*readnparse(char *filename, t_map *mastermap);
int			key_event(int keycode, t_map *mastermap);
void    img_pixel_put(t_img *img, int x, int y, int color);
void	initialize(t_map *mastermap);
void	draw_map(t_map *mastermap);
void	calculate_proj(t_map *mastermap);
float   **ft_memalloc_matrix(size_t size);
void    matrix_compute_to_projected(t_cords *mapcords, int i, float **matrix);
void    translation(t_map *mastermap);
void    ft_free_matrix(float **matrix, size_t size);
void    matrix_compute_projected(t_cords *mapcords, int i, float **matrix);
void	scalation(t_map *mastermap);
void    rotation_x(t_map *mastermap);
void    rotation_y(t_map *mastermap);
void    rotation_z(t_map *mastermap);
void    perspection(t_map *mastermap);
void    orthogration(t_map *mastermap);
void    reflection(t_map *mastermap);
void    matrix_compute_perspective(t_cords *mapcords, int i, float **matrix);
void	free_mlx(t_map *mastermap);

#endif
