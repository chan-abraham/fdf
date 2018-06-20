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

/*
**  this function puts in the projected x and y cords that is set up for further
**  calculations. typically, in the matrix[3][3], others write that as a '0'
**  because they are discarding the z information. i do not do that here because
**  i want to preserve the z information for further transformations. zeroing
**  out the z information doesnt matter for this project because we are
**  only using the calculated x and y information in drawing anyway.
**  (z is only used to calculate the x and y positions during transformation) 
*/
/*
void    reflection(t_map *mastermap)
{
    {
    float   **matrix;
    int i;
    
    matrix = ft_memalloc_matrix(4);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = -1;
    matrix[3][3] = 1;
    i = 0;
    while (i < mastermap->pointcount)
        matrix_compute_projected(mastermap->mapcords, i++, matrix);
    ft_free_matrix(matrix, 4);
    }
}
*/
void    orthogration(t_map *mastermap)
{
    {
    float   **matrix;
    int i;
    
    matrix = ft_memalloc_matrix(4);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    i = 0;
    while (i < mastermap->pointcount)
        matrix_compute(mastermap->mapcords, i++, matrix);
    ft_free_matrix(matrix, 4);
    }
}

void    perspection(t_map *mastermap)
{
    {
    float   **matrix;
    int i;
    
    matrix = ft_memalloc_matrix(4);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    matrix[3][2] = DISTANCE;
    i = 0;
    while (i < mastermap->pointcount)
        matrix_compute_perspective(mastermap->mapcords, i++, matrix);
    ft_free_matrix(matrix, 4);
    }
}