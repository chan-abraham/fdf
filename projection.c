/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:54:15 by abchan            #+#    #+#             */
/*   Updated: 2018/06/12 17:54:20 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    calculate_proj(t_map *mastermap)
{/*
    int i;
    i = 0;
    while (i < mastermap->pointcount)
    {
        mastermap->mapcords[i].px = mastermap->mapcords[i].x;
        mastermap->mapcords[i].py = mastermap->mapcords[i].y;
        i++;
    }
    */
    if (mastermap->perspective)
        perspection(mastermap);
    else
        orthogration(mastermap);
    //reflection(mastermap);
    if (mastermap->rotatez)
        rotation_z(mastermap);
    if (mastermap->rotatey)
        rotation_y(mastermap);
    if (mastermap->rotatex)
        rotation_x(mastermap);
    scalation(mastermap);
    if (mastermap->xtrans != 0 || mastermap->ytrans != 0)
        translation(mastermap);
    ft_putstr("printing below VVVVVV");
    ft_putchar('\n');
    ft_putnbr(mastermap->mapcords[0].px);
    ft_putchar(',');
    ft_putnbr(mastermap->mapcords[0].py);
    ft_putchar('\n');
    /*
    if (mastermap->perspective != 0)
        apply_perspective(mastermap->mapcords);
    else
        apply_orthographic(mastermap->mapcords);
    */ 
}