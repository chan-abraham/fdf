/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyninit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 20:12:42 by abchan            #+#    #+#             */
/*   Updated: 2018/05/29 20:12:44 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize(t_map *mastermap)
{
	mlx_clear_window(mastermap->mlx, mastermap->win);
	mastermap->xtrans = WNDW_WDTH / 2;
	mastermap->ytrans = WNDW_HGHT / 2;
	mastermap->scale = WNDW_WDTH / (mastermap->mapwidth * 3);
	mastermap->rotatex = -5;
	mastermap->rotatey = 0;
	mastermap->rotatez = 2;
	mastermap->perspective = 0;
//	mlx_put_image_to_window(mastermap->mlx, mastermap->win, mastermap->img->ptr, 0, 0);
}

int		key_event(int keycode, t_map *mastermap)
{
	ft_putstr("the keycode is");
	ft_putchar('-');
	ft_putnbr(keycode);
	ft_putchar('-');
//	ft_bzero(mastermap->img->ptr, WNDW_HGHT * WNDW_WDTH * mastermap->img->bbp);
	if (keycode == ESCKEY)
	{//free shit here
		mlx_destroy_window(mastermap->mlx, mastermap->win);
		exit(0);
	}
	if (keycode == AKEY || keycode == DKEY)
		mastermap->xtrans += (keycode == AKEY) ? -TRANSLAT_AMT : +TRANSLAT_AMT;//translate x
	if (keycode == WKEY || keycode == SKEY)
		mastermap->ytrans += (keycode == SKEY) ? +TRANSLAT_AMT : -TRANSLAT_AMT;//translate y
	if (keycode == PLUS || keycode == MINUS)
		mastermap->scale += (keycode == PLUS) ? +SCALE_AMT : -SCALE_AMT;//scales
	if (keycode == QKEY || keycode == EKEY)
		mastermap->rotatez += (keycode == EKEY) ? 1 : -1;//rotate
	if (keycode == ONEKEY || keycode == TWOKEY)
		mastermap->rotatey += (keycode == TWOKEY) ? -1 : +1;//rotate
	if (keycode == RKEY || keycode == FKEY)
		mastermap->rotatex += (keycode == RKEY) ? -1 : +1;//rotate
	if (keycode == PKEY)
		mastermap->perspective = (mastermap->perspective == 0) ? 1 : 0;//turn perspective mode on
	if (keycode == SPACKEY)
		initialize(mastermap);//reset
	calculate_proj(mastermap);
//	ft_putnbr(mastermap->rotatey);
//	ft_putchar(',');
//	ft_putnbr(mastermap->rotatex);
//	ft_putchar('\n');
	
//	ft_putnbr(mastermap->mapcords[0].px);
//	ft_putchar(',');
//	ft_putnbr(mastermap->mapcords[0].py);
//	ft_putchar('\n');
	draw_map(mastermap);
	return (0);
}