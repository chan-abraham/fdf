/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:54:15 by abchan            #+#    #+#             */
/*   Updated: 2018/06/22 14:49:44 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_to_origin(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = 1;
	matrix[0][3] = -(mastermap->mapwidth / 2);
	matrix[1][1] = 1;
	matrix[1][3] = -((mastermap->pointcount / mastermap->mapwidth) / 2);
	matrix[2][2] = 1;
	matrix[2][3] = (-(mastermap->maxmapdepth - mastermap->minmapdepth) / 2);
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_to_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

void	calculate_proj(t_map *mastermap)
{
	move_to_origin(mastermap);
	rotation_z(mastermap);
	rotation_y(mastermap);
	rotation_x(mastermap);
	if (!mastermap->perspective)
	{
		scalation(mastermap);
		translation(mastermap);
	}
	if (mastermap->perspective)
	{
		perspection(mastermap);
		scalation(mastermap);
		translation(mastermap);
	}
	else
		orthogration(mastermap);
}
