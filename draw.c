/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:16:59 by abchan            #+#    #+#             */
/*   Updated: 2018/06/23 11:05:02 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** this function is gifted from jkimmina. he didnt use the new image funtion on
** his fdf, but he said i shuold use it on mine because it will make it run more
** efficiently. he originally created this function for his fractol. the point
** of this function is to put into the image what color pixel is at the specific
** data address. the *(int *) part is to cast the result as an int.
*/

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WNDW_WDTH && y >= 0 && y < WNDW_HGHT)
		*(int *)(img->data_addr + (x + y * WNDW_WDTH) * img->bbp) = color;
}

/*
** **NOTE** if you are reading this code with the hopes to learn how to do a
** color gradient, i'd advise you to look at someone elses code**
**
** this function would have been a great opportunity to learn about learning
** how to manipulate hexadecimal, but i spent so much time learning about
** matrices and perspective projections, so at this point in the project, i
** just want to turn it in. so heres this really ugly color gradient function
** that, mostly, works, and has no flexibility. it takes in the paramaters
** which are mostly a way of getting past norm, determines the direction
** at which the line is being drawn (positive or negative slope) and returns
** a gradually darkening of the color dependent on the former. if the slope
** is flat, it calculates the color based on the height. the part of the
** function with the power of 16 and stuff is how decimal is converted
** into hex if it were a stable (rgb all increasing at the same time)
** gradient.
*/

long	get_color(t_map *mastermap, float steps, float z, float color)
{
	long	value;
	long	slope;
	int		i;

	if (!mastermap->color)
		return (0xFFFFFF);
	slope = 0;
	value = 0;
	if (color > 0)
		slope = 1;
	else if (color < 0)
		slope = -1;
	if (slope == 1)
		value = steps / (8 * color) * 64;
	else if (slope == -1)
		value = (fabsf(color) - steps) / (8 * fabsf(color)) * 64;
	else if (slope == 0)
		value = -z / (fabsf((float)mastermap->minmapdepth) +
				fabsf((float)mastermap->maxmapdepth)) * 128;
	i = 5;
	while (i >= 0)
		slope = slope + pow(16, i--);
	slope = slope * value;
	return ((5521727 + slope) > 0xFFFFFF ? 0xFFFFFF : (5521727 + slope));
}

/*
** this is the function that connects the dots. some (one) of the variable
** naming convention may be questionable, but i only did it to get through
** norminette.
**
** there are two main line drawing algorithms that people haved used on this
** project. Bresenham's line algorithm, and this one, "digital differential
** analyzer". despite the more technical sounding name, the concept behind
** dda is much easier to understand and write into code (I.M.O.).
**
** the colors thing is to determine the slope of the line, not used in
** this function to draw the line, but to use in the get_color function
** as a means to know which way to gradiate. i probably wouldn't have
** this function in this exact way if not for norminette.
*/

void	draw_line(t_map *mastermap, t_cords first, t_cords second)
{
	float	dx;
	float	dy;
	float	steps;
	float	fucknorminette[2];
	float	color;

	dx = second.px - first.px;
	dy = second.py - first.py;
	steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
	dx = dx / steps;
	dy = dy / steps;
	color = first.z < second.z ? steps : -steps;
	color = (first.z == second.z) ? 0 : color;
	fucknorminette[0] = first.px;
	fucknorminette[1] = first.py;
	while (steps >= 0)
	{
		img_pixel_put(mastermap->img, fucknorminette[0], fucknorminette[1],
				get_color(mastermap, steps, first.z, color));
		fucknorminette[0] = fucknorminette[0] + dx;
		fucknorminette[1] = fucknorminette[1] + dy;
		steps--;
	}
}

/*
** this clears the image memory
*/

void	clear_img(t_img *img)
{
	ft_bzero(img->data_addr, WNDW_HGHT * WNDW_WDTH * img->bbp);
}

/*
** this function is the central core of the drawing part of this program.
** i didnt do anything weird here.
*/

void	draw_map(t_map *mastermap)
{
	int		x;
	int		y;

	clear_img(mastermap->img);
	y = 0;
	while (y < mastermap->mapheight)
	{
		x = 0;
		while (x < mastermap->mapwidth)
		{
			if (x < mastermap->mapwidth - 1)
				draw_line(mastermap, mastermap->mapcords[x +
						(mastermap->mapwidth * y)], mastermap->mapcords[(x +
							1) + (mastermap->mapwidth * y)]);
			if (y < mastermap->mapheight - 1)
				draw_line(mastermap, mastermap->mapcords[x +
						(mastermap->mapwidth * y)], mastermap->mapcords[x +
						(mastermap->mapwidth * (y + 1))]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mastermap->mlx, mastermap->win,
			mastermap->img->ptr, 0, 0);
}
