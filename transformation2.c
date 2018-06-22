/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 19:47:06 by abchan            #+#    #+#             */
/*   Updated: 2018/06/19 19:47:09 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    orthogration(t_map *mastermap)
{
    {
    float   **matrix;
    int i;
    
    matrix = ft_memalloc_matrix(4);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 0;
    matrix[3][3] = 1;
    i = 0;
    while (i < mastermap->pointcount)
        matrix_compute_projected(mastermap->mapcords, i++, matrix);
    ft_free_matrix(matrix, 4);
    }
}

void    perspection(t_map *mastermap)
{
    {
    float   **matrix;
    int i;
    
    matrix = ft_memalloc_matrix(4);
    matrix[0][0] = 750;
    matrix[1][1] = 750;
    matrix[2][2] = 750;
    matrix[2][3] = 0;
    matrix[3][3] = 0;
    matrix[3][2] = 25;
    i = 0;
    while (i < mastermap->pointcount)
        matrix_compute_perspective(mastermap->mapcords, i++, matrix);
    i++;
    ft_free_matrix(matrix, 4);
    }
}