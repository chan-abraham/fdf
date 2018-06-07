/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:42:21 by abchan            #+#    #+#             */
/*   Updated: 2018/05/13 15:42:26 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <stdio.h>

t_img	*init_img(void *mlx)
{
	t_img	*img;
	
	if (!(img = (t_img *)ft_memalloc(sizeof(t_img))))
		return (0);
	if (!(img->ptr = mlx_new_image(mlx, WNDW_WDTH, WNDW_HGHT)))
		return (0);
	img->data_addr = mlx_get_data_addr(img->ptr, &img->bbp, &img->line_size, &img->endian);
	img->bbp /= 8;
	return (img);
}

int		main(int argc, char **argv)
{
	t_map	*mastermap;
	
	if (!(mastermap = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (argc == 2)
	{
		if (!(mastermap = readnparse(argv[1], mastermap)))
			return (0);
		mastermap->mlx = mlx_init();
		mastermap->win = mlx_new_window(mastermap->mlx, WNDW_WDTH, WNDW_HGHT, "FDF");
		mastermap->img = init_img(mastermap->img);
		mlx_key_hook(mastermap->win , key_event, mastermap);
		mlx_string_put(mastermap->mlx, mastermap->win, WNDW_WDTH, WNDW_HGHT, 0xff00ff, "hi :) \n press space to begin");
		mlx_put_image_to_window(mastermap->mlx, mastermap->win, mastermap->img->ptr, 0, 0);
		mlx_loop(mastermap->mlx);
	}
	else
		ft_putendl("Error: Input");

	
	return (0);
}