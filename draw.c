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
/*
void    draw_line(t_map *mastermap, t_cords first, t_cords second)
{
    float   dx;
    float   dy;
    float   p;
    float   x;
    float   y;

    dx = fabsf(second.px - first.px);
    dy = fabsf(second.py - first.py);
    x = first.px;
    y = first.py;
    p = 2 * dy - dx;
    while(x < second.px)
    {
        if (p >= 0)
        {
            img_pixel_put(mastermap->img, x, y, 0xFFFFFF);
            y = y + 1;
            p = p + 2 * dy;
        }
        else
        {
            img_pixel_put(mastermap->img, x, y, 0xFFFFFF);
            p = p + 2 * dy;
        }
        x = x + 1;
    }
}
*/

void    draw_line(t_map *mastermap, t_cords first, t_cords second)
{
    float   dx;
    float   dy;
    float   steps;
    float   x;
    float   y;

    dx = second.px - first.px;
    dy = second.py - first.py;
    steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
    dx = dx / steps;
    dy = dy / steps;
    x = first.px;
    y = first.py;
    while (steps >= 0)
    {
        img_pixel_put(mastermap->img, x, y, 0xFFFFFF);
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