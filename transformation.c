/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 09:25:51 by abchan            #+#    #+#             */
/*   Updated: 2018/06/22 14:55:15 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_z(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = cosf(mastermap->rotatez * (M_PI_4 / 4));
	matrix[0][1] = -sinf(mastermap->rotatez * (M_PI_4 / 4));
	matrix[1][0] = sinf(mastermap->rotatez * (M_PI_4 / 4));
	matrix[1][1] = cosf(mastermap->rotatez * (M_PI_4 / 4));
	matrix[2][2] = 1;
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

void	rotation_x(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = 1;
	matrix[1][1] = cosf(mastermap->rotatex * (M_PI_4 / 4));
	matrix[1][2] = -sinf(mastermap->rotatex * (M_PI_4 / 4));
	matrix[2][1] = sinf(mastermap->rotatex * (M_PI_4 / 4));
	matrix[2][2] = cosf(mastermap->rotatex * (M_PI_4 / 4));
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

void	rotation_y(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = cosf(mastermap->rotatey * (M_PI_4 / 4));
	matrix[0][2] = sinf(mastermap->rotatey * (M_PI_4 / 4));
	matrix[1][1] = 1;
	matrix[2][0] = -sinf(mastermap->rotatey * (M_PI_4 / 4));
	matrix[2][2] = cosf(mastermap->rotatey * (M_PI_4 / 4));
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

void	scalation(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = mastermap->scale;
	matrix[1][1] = mastermap->scale;
	matrix[2][2] = mastermap->scale;
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

void	translation(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
	matrix[0][3] = mastermap->xtrans;
	matrix[1][3] = mastermap->ytrans;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}
