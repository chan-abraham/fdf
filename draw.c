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

void    draw_line(t_map *mastermap, t_cords first, t_cords second)
{
    img_pixel_put(mastermap->img, i++, WNDW_HGHT / 2, 0xFFFFFF);
}


void    draw_map(t_map *mastermap)
{
    int x;
    int y;

    y = 0;
    while (y < mastermap->mapheight - 1)
    {
        x = 0;
        while (x < mastermap->mapwidth - 1)
        {
            draw_line(mastermap, mastermap->mapcords[x + (mastermap->mapwidth * y)],
            mastermap->mapcords[(x + 1) + (mastermap->mapwidth * y)]);
            if (y < mastermap->mapheight - 1)
                draw_line(mastermap, mastermap->mapcords[x + (mastermap->mapwidth * y)],
                mastermap->mapcords[x + (mastermap->mapwidth * (y + 1))]);
            x++;
        }
        y++;
    }
}