/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readnparse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 09:17:57 by abchan            #+#    #+#             */
/*   Updated: 2018/06/23 10:34:33 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** this sets the min and max depth as it is being passed through the readmap
** function.
*/

void	find_depth_z(t_map *mastermap, float z)
{
	if ((int)z > mastermap->maxmapdepth)
		mastermap->minmapdepth = z;
	if ((int)z < mastermap->minmapdepth)
		mastermap->maxmapdepth = z;
}

void	pass_that_norm(char **nbrsplit, char *line)
{
	ft_memdel((void **)&nbrsplit);
	ft_memdel((void **)&line);
}

/*
** here the map is being read and put into the data structure. at the same time,
** i am also setting the homocord constant, which is needed for the perspective
** projection. i technically dont need to save the homocord information, but
** i did it more as a representation of the math that is going on in this
** program. the max depth and min depth is also determined here. the reason
** z is saved as -z is because (from my understanding) a positive z on our
** screen is deeper on our screen, where as according to our map, we actually
** want a positive z to come out at us.
*/

t_cords	*readmap(t_map *mastermap, int fd, t_cords *mapcords)
{
	char	*line;
	int		i;
	int		wordcount;
	int		j;
	char	**nbrsplit;

	i = 0;
	while (get_next_line(fd, &line))
	{
		j = -1;
		wordcount = ft_wordcount(line, ' ');
		nbrsplit = ft_strsplit(line, ' ');
		while (j++ < wordcount - 1)
		{
			mapcords[i * wordcount + j].x = (float)j;
			mapcords[i * wordcount + j].y = (float)i;
			mapcords[i * wordcount + j].z = -(float)ft_atoi(nbrsplit[j]);
			find_depth_z(mastermap, mapcords[i * wordcount + j].z);
			mapcords[i * wordcount + j].homocord = 1;
			ft_memdel((void **)&nbrsplit[j]);
		}
		pass_that_norm(nbrsplit, line);
		i++;
	}
	return (mapcords);
}

/*
** 1) this function will read the map, return the value of total map points,
** and make sure the number of characters in each line is equal.
** if it is not, it will return 0. I know I should be setting this data
** instead in linked list to prevent reading again later, so I'll change this
** if this is too inefficient to function or if I stop being lazy.
** 2) ok nevermind, I took this opportunity to initialize a few things,
** so... not going to change it.
*/

int		countmap(char *filename, t_map *mastermap)
{
	int		i;
	int		fd;
	int		wordcount;
	char	*line;

	i = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (i == 0)
			wordcount = ft_wordcount(line, ' ');
		if (i > 0 && ft_wordcount(line, ' ') != wordcount)
			return (0);
		ft_memdel((void **)&line);
		i++;
	}
	mastermap->mapwidth = wordcount;
	mastermap->mapheight = i;
	mastermap->maxmapdepth = 0;
	mastermap->minmapdepth = 0;
	mastermap->initializekey = 0;
	close(fd);
	return (wordcount * i);
}

t_map	*readnparse(char *filename, t_map *mastermap)
{
	int		fd;
	t_cords	*mapcords;

	if ((mastermap->pointcount = countmap(filename, mastermap)) == 0)
	{
		ft_putendl("Error: Invalid Map");
		return (NULL);
	}
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putendl("Error: Read");
		return (NULL);
	}
	if (!(mapcords = (t_cords *)ft_memalloc(sizeof(t_cords) *
					mastermap->pointcount)))
	{
		ft_putendl("Error: Malloc");
		return (NULL);
	}
	if ((mastermap->mapcords = readmap(mastermap, fd, mapcords)) == NULL)
		return (NULL);
	close(fd);
	return (mastermap);
}
