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


/*
** about the keycodes: initially when I made this program, I was using a full
** keyboard with a numberpad. Using that, it was a more intuitive interface to
** put some of the rotation and feature keys on there. However, after a few
** months, when I got a laptop, I realized that my fdf didn't work fully on my
** laptop because it doesnt have a numpad!!! So, as i am writing this, I am
** rekeying the keys so this program would work on the laptop. (I decided not to
** change the macro names for the keys because lazy, but maybe i'll change it
** later.)
**
** side note, while writing this, the thought came in to mind a language
** encryption system based on the keycode. Probably an idea thought of by many
** novice programmers, but I'd thought I'd document this thought anyway.
** 09/21/18 - sfo on the way to Pittsburgh to visit emilee
** side side note, while writing this, i thought it might be nice to document
** my comments with my location and just what I am doing/thoughts while I'm
** doing this. maybe it will make a more fun way to read it.
*/

#define ESCKEY 53
#define WKEY 13
#define AKEY 0
#define SKEY 1
#define DKEY 2
#define ONEKEY 258 //shift key now
#define TWOKEY 125 //down arrow
#define THREEKEY 44 //'/' key
#define FOURKEY 123 // <-
#define FIVEKEY 87 //don't know why i even keyed this
#define SIXKEY 124 //->
#define QKEY 12
#define EIGHTKEY 126 // up arrow
#define EKEY 14
#define PLUSKEY 24
#define MINUSKEY 27
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
			ft_putendl("**********************************");
			ft_putendl("**WASD = translation**************");
			ft_putendl("**UP & DOWN ARROW = x axis rotate*");
			ft_putendl("**<- & -> = y axis rotate*********");
			ft_putendl("**QE = z axis rotate**************");
			ft_putendl("** + & - = scale******************");
			ft_putendl("**SHIFT = perspective toggle******");
			ft_putendl("**/ = color toggle****************");
			ft_putendl("**SPACE BAR = reset***************");
			ft_putendl("**ESC = EXIT**********************");
			ft_putendl("**********************************");
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
