/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyninit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 20:12:42 by abchan            #+#    #+#             */
/*   Updated: 2018/06/23 12:24:40 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ESCKEY 53
#define WKEY 13
#define AKEY 0
#define SKEY 1
#define DKEY 2
#define ONEKEY 83
#define TWOKEY 84
#define THREEKEY 85
#define FOURKEY 86
#define FIVEKEY 87
#define SIXKEY 88
#define QKEY 12
#define EIGHTKEY 91
#define EKEY 14
#define PLUSKEY 78
#define MINUSKEY 69
#define SPACKEY 49

void	free_mlx(t_map *mastermap)
{
	int		i;

	i = 0;
	ft_memdel((void **)&mastermap->img);
	ft_memdel((void **)&mastermap->mapcords);
	ft_memdel((void **)&mastermap);
}

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
	mastermap->color = 0;
	mastermap->initializekey = 1;
}

int		key_event_two(int keycode, t_map *mastermap)
{
	if (keycode == SPACKEY)
	{
		if (!mastermap->initializekey)
		{
			ft_putendl("*********************************");
			ft_putendl("**WASD = translation*************");
			ft_putendl("**NUMPAD 2 & 8 = x axis rotate***");
			ft_putendl("**NUMPAD 4 & 6 = y axis rotate***");
			ft_putendl("**QE = z axis rotate*************");
			ft_putendl("**NUMPAD + & - = scale***********");
			ft_putendl("**NUMPAD 1 = perspective toggle**");
			ft_putendl("**NUMPAD 3 = color toggle********");
			ft_putendl("**SPACE BAR = reset**************");
			ft_putendl("**ESC = EXIT*********************");
			ft_putendl("*********************************");
		}
		initialize(mastermap);
	}
	if (mastermap->initializekey)
	{
		calculate_proj(mastermap);
		draw_map(mastermap);
	}
	return (0);
}

int		key_event(int keycode, t_map *mastermap)
{
	if (keycode == ESCKEY)
	{
		free_mlx(mastermap);
		mlx_destroy_window(mastermap->mlx, mastermap->win);
		exit(0);
	}
	if (keycode == AKEY || keycode == DKEY)
		mastermap->xtrans += (keycode == AKEY) ? -TRANSLAT_AMT : +TRANSLAT_AMT;
	if (keycode == WKEY || keycode == SKEY)
		mastermap->ytrans += (keycode == SKEY) ? +TRANSLAT_AMT : -TRANSLAT_AMT;
	if (keycode == PLUSKEY || keycode == MINUSKEY)
		mastermap->scale += (keycode == PLUSKEY) ? -SCALE_AMT : SCALE_AMT;
	if (keycode == QKEY || keycode == EKEY)
		mastermap->rotatez += (keycode == EKEY) ? 1 : -1;
	if (keycode == FOURKEY || keycode == SIXKEY)
		mastermap->rotatey += (keycode == SIXKEY) ? -1 : 1;
	if (keycode == EIGHTKEY || keycode == TWOKEY)
		mastermap->rotatex += (keycode == TWOKEY) ? 1 : -1;
	if (keycode == ONEKEY)
		mastermap->perspective = (mastermap->perspective == 0) ? 1 : 0;
	if (keycode == THREEKEY)
		mastermap->color = (mastermap->color == 0) ? 1 : 0;
	key_event_two(keycode, mastermap);
	return (0);
}
