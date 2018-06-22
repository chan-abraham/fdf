/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:16:59 by abchan            #+#    #+#             */
/*   Updated: 2018/06/05 14:17:01 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** this function is gifted from jkimmina. he didnt use the new image funtion on
** his fdf, but he said i shuold use it on mine because it will make it run more
** efficiently. he originally created this function for his fdf.
*/
void    img_pixel_put(t_img *img, int x, int y, int color)
{
    if (x >= 0 && x < WNDW_WDTH && y >= 0 && y < WNDW_HGHT)
        *(int *)(img->data_addr + (x + y * WNDW_WDTH) * img->bbp) = color;
}

long     get_color(t_map *mastermap, float steps, float z, float color)
{
    long     value;
    long     slope;
    int     i;

    if (!mastermap->color)
        return (0xFFFFFF);
    slope = 0;
    value = 0;
    if (color > 0)
        slope = 1;
    else if (color < 0)
        slope = -1;
    if (slope == 1)
        value = steps / (8 *color) * 64;
    else if (slope == -1)
        value = (fabsf(color) - steps) / (8 * fabsf(color)) * 64;
    else if (slope == 0)
        value = -z / (fabsf((float)mastermap->minmapdepth) + fabsf((float)mastermap->maxmapdepth)) * 128;
    i = 5;
    while (i >= 0)
        slope = slope + pow(16, i--);
    slope = slope * value;
    return (/*5534609*/ 5521727 + slope);
}

void    draw_line(t_map *mastermap, t_cords first, t_cords second)
{
    float   dx;
    float   dy;
    float   steps;
    float   x;
    float   y;
    float   color;
    
    dx = second.px - first.px;
    dy = second.py - first.py;
    steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
    dx = dx / steps;
    dy = dy / steps;
  //  printf("%.6f,", first.z);
    //printf("%.6f,", first.x);
  //  printf("%.6f,", first.y);
   // printf("%.6f,\n", second.z);
        
    color = first.z < second.z ? steps : -steps;
    color = (first.z == second.z) ? 0 : color; 
   // printf("%.6f,", first.z);
   // printf("%.6f,\n", second.z);
    x = first.px;
    y = first.py;
    while (steps >= 0)
    {
        img_pixel_put(mastermap->img, x, y, get_color(mastermap, steps, first.z, color));
      /*  printf("%.6f", first.z);
        ft_putchar(',');
        printf("%.6f", second.z);
        ft_putchar(',');
        ft_putnbr((int)color);
        ft_putchar(',');
        ft_putnbr((int)steps);
        ft_putchar(',');
        ft_putnbr(get_color(mastermap, steps, first.z, color));
        ft_putchar('\n');*/
        x = x + dx;
        y = y + dy;
        steps--;
    }
}

void    clear_img(t_img *img)
{
    ft_bzero(img->data_addr, WNDW_HGHT * WNDW_WDTH * img->bbp);
}

void    draw_map(t_map *mastermap)
{
    int x;
    int y;
    clear_img(mastermap->img);
    y = 0;
    while (y < mastermap->mapheight)
    {
        x = 0;
        while (x < mastermap->mapwidth)
        {
            if (x < mastermap->mapwidth - 1)
                draw_line(mastermap, mastermap->mapcords[x + (mastermap->mapwidth * y)],
                    mastermap->mapcords[(x + 1) + (mastermap->mapwidth * y)]);
            if (y < mastermap->mapheight - 1)
                draw_line(mastermap, mastermap->mapcords[x + (mastermap->mapwidth * y)],
                    mastermap->mapcords[x + (mastermap->mapwidth * (y + 1))]);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mastermap->mlx, mastermap->win, mastermap->img->ptr, 0, 0);
}