/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:53:48 by abchan            #+#    #+#             */
/*   Updated: 2018/06/16 10:53:51 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    ft_free_matrix(float **matrix, size_t size)
{
    size_t  i;

    i = 0;
    while (i < size)
        ft_memdel((void **)&matrix[i++]);
    ft_memdel((void **)&matrix);
}

// void    matrix_compute(t_cords mapcords, float **matrix)
/*
void    matrix_compute_perspective(t_cords *mapcords, int i, float **matrix)
{
  //   float tmpx;
   // float tmpy;
   // float tmpz;

  //  tmpx = mapcords[i].px;
  //  tmpy = mapcords[i].py;
  //  tmpz = mapcords[i].pz;

 //   tmpz = mapcords[i].z + DISTANCE;
 //   mapcords[i].px = tmpx * matrix[0][0] + tmpx * (matrix[3][2] / tmpz);/// matrix[3][2]);// / mapcords[i].z);
 //   mapcords[i].py = tmpy * matrix[1][1] +(tmpy) * (matrix[3][2] / tmpz);/// matrix[3][2]);// / mapcords[i].z);
     


    
    float tmpz;
    float   homo;
    float tmpx;
    float tmpy;
   // float tmpz;
      
    homo = 1;
    //tmpz = mapcords[i].pz + DISTANCE;

    //tmpz = mapcords[i].pz / DISTANCE;
  tmpx = (mapcords[i].px);/// matrix[3][2]);// / mapcords[i].z);
    tmpy = (mapcords[i].py);/// matrix[3][2]);// / mapcords[i].z);
    tmpz = mapcords[i].pz;
    homo = 25 * mapcords[i].pz + 1;
    tmpx /= homo;
    tmpy /= homo;
    tmpz /= homo;
   
    mapcords[i].px = matrix[0][0] * tmpx + matrix[0][1] * tmpy +
       matrix[0][2] * tmpz + matrix[0][3] * mapcords[i].homocord;
    mapcords[i].py = matrix[1][0] * tmpx + matrix[1][1] * tmpy +
       matrix[1][2] * tmpz + matrix[1][3] * mapcords[i].homocord;
    mapcords[i].pz = matrix[2][0] * tmpx + matrix[2][1] * tmpy +
       matrix[2][2] * tmpz + matrix[2][3] * mapcords[i].homocord;
    homo = matrix[3][0] * tmpx + matrix[3][1] * tmpy +
       matrix[3][2] * tmpz + matrix[3][3] * mapcords[i].homocord;
    
    mapcords[i].px /= homo;
    mapcords[i].py /= homo;
    mapcords[i].pz /= homo;
    
  //  tmpz = mapcords[i].z + DISTANCE;
  //  mapcords[i].px = (mapcords[i].x) * (matrix[3][2] / tmpz);/// matrix[3][2]);// / mapcords[i].z);
  //  mapcords[i].py = (mapcords[i].y) * (matrix[3][2] / tmpz);/// matrix[3][2]);// / mapcords[i].z);
   //  mapcords[i].pz = matrix[2][0] * mapcords[i].x + matrix[2][1] * mapcords[i].y +
   //    matrix[2][2] * mapcords[i].z + matrix[2][3] * mapcords[i].homocord;


}
*/

void    matrix_compute_perspective(t_cords *mapcords, int i, float **matrix)
{
    float tmpx;
    float tmpy;
    float tmpz;
    float homo;

    tmpx = mapcords[i].px;
    tmpy = mapcords[i].py;
    tmpz = mapcords[i].pz;
    tmpz += 25;
    mapcords[i].px = matrix[0][0] * tmpx + matrix[0][1] * tmpy + matrix[0][2] *
        tmpz + matrix[0][3] * mapcords[i].homocord;
    mapcords[i].py = matrix[1][0] * tmpx + matrix[1][1] * tmpy + matrix[1][2] *
        tmpz + matrix[1][3] * mapcords[i].homocord;
    mapcords[i].pz = matrix[2][0] * tmpx + matrix[2][1] * tmpy + matrix[2][2] *
        tmpz + matrix[2][3] * mapcords[i].homocord;
    homo = matrix[3][0] * tmpx + matrix[3][1] * tmpy + matrix[3][2] *
        tmpz + matrix[3][3] * mapcords[i].homocord;
    if (homo != 1)
    {
        mapcords[i].px /= homo;
        mapcords[i].py /= homo;
        mapcords[i].pz /= homo;
    }
     
}



void    matrix_compute_projected(t_cords *mapcords, int i, float **matrix)
{
    float tmpx;
    float tmpy;
    float tmpz;
    float homo;

   

    tmpx = mapcords[i].px;
    tmpy = mapcords[i].py;
    tmpz = mapcords[i].pz;
    mapcords[i].px = matrix[0][0] * tmpx + matrix[0][1] * tmpy + matrix[0][2] *
        tmpz + matrix[0][3] * mapcords[i].homocord;
    mapcords[i].py = matrix[1][0] * tmpx + matrix[1][1] * tmpy + matrix[1][2] *
        tmpz + matrix[1][3] * mapcords[i].homocord;
    mapcords[i].pz = matrix[2][0] * tmpx + matrix[2][1] * tmpy + matrix[2][2] *
        tmpz + matrix[2][3] * mapcords[i].homocord;
    homo = matrix[3][0] * tmpx + matrix[3][1] * tmpy + matrix[3][2] *
        tmpz + matrix[3][3] * mapcords[i].homocord;
    if (homo != 1)
    {
        mapcords[i].px /= homo;
        mapcords[i].py /= homo;
        mapcords[i].pz /= homo;
    }
  //   ft_putnbr((int)mapcords[i].px);
  //  ft_putchar(',');
   // ft_putnbr((int)mapcords[i].py);
  //  ft_putchar(',');
  //  ft_putnbr((int)mapcords[i].pz);
   // ft_putchar('\n');
}

void    matrix_compute_to_projected(t_cords *mapcords, int i, float **matrix)
{
    mapcords[i].px = matrix[0][0] * mapcords[i].x + matrix[0][1] * mapcords[i].y +
        matrix[0][2] * mapcords[i].z + matrix[0][3] * mapcords[i].homocord;
    mapcords[i].py = matrix[1][0] * mapcords[i].x + matrix[1][1] * mapcords[i].y +
        matrix[1][2] * mapcords[i].z + matrix[1][3] * mapcords[i].homocord;
    mapcords[i].pz = matrix[2][0] * mapcords[i].x + matrix[2][1] * mapcords[i].y +
        matrix[2][2] * mapcords[i].z + matrix[2][3] * mapcords[i].homocord;
   // ft_putnbr((int)mapcords[i].px);
   // ft_putchar(',');
   // ft_putnbr((int)mapcords[i].py);
   // ft_putchar(',');
   // ft_putnbr((int)mapcords[i].pz);
   // ft_putchar('\n');
}


float   **ft_memalloc_matrix(size_t size)
{
    float   **matrix;
    size_t  i;

    i = 0;
    if (!(matrix = (float **)ft_memalloc(sizeof(float *) * size)))
        return (0);
    while (i < size)
    {
        if(!(matrix[i++] = (float *)ft_memalloc(sizeof(float) * size)))
        return (0);
    }
    return (matrix);
}