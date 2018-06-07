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
	mastermap->xtrans = 0;
	mastermap->ytrans = 0;
	mastermap->rotate = 0;
	mastermap->perspective = 0;
}

int		key_event(int keycode, t_map *mastermap)
{
	mlx_clear_window(mastermap->mlx, mastermap->win);
	if (keycode == ESCKEY)
	{
		mlx_destroy_window(mastermap->mlx, mastermap->win);
		exit(0);
	}
	if (keycode == AKEY || keycode == DKEY)
		mastermap->xtrans += (keycode == AKEY) ? -1 : +1;//translate x
	if (keycode == WKEY || keycode == SKEY)
		mastermap->ytrans += (keycode == SKEY) ? -1 : +1;//translate y
	if (keycode == QKEY || keycode == EKEY)
		mastermap->rotate += (keycode == EKEY) ? -1 : +1;//rotate
	if (keycode == PKEY)
		mastermap->perspective = (mastermap->perspective == 0) ? 1 : 0;//turn perspective mode on
	if (keycode == SPACKEY)
		initialize(mastermap);//reset
	draw_map(mastermap);
	return (0);
}