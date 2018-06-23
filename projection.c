/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:54:15 by abchan            #+#    #+#             */
/*   Updated: 2018/06/23 12:09:01 by abchan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** this function moves the information around the origin
*/

void	move_to_origin(t_map *mastermap)
{
	float	**matrix;
	int		i;

	matrix = ft_memalloc_matrix(4);
	matrix[0][0] = 1;
	matrix[0][3] = -(mastermap->mapwidth / 2);
	matrix[1][1] = 1;
	matrix[1][3] = -((mastermap->pointcount / mastermap->mapwidth) / 2);
	matrix[2][2] = 1;
	matrix[2][3] = (-(mastermap->maxmapdepth - mastermap->minmapdepth) / 2);
	matrix[3][3] = 1;
	i = 0;
	while (i < mastermap->pointcount)
		matrix_compute_to_projected(mastermap->mapcords, i++, matrix);
	ft_free_matrix(matrix, 4);
}

/*
** this is the central core of projecting the map, where where i spent the
** majority of my time and energy during this project (other than doing nothing
** and wasting my time).
**
** a good friend of mine, juo, did his project using matrices, and told me i
** should do the same because it'd be easier. algorithm wise, yes it is easier,
** but doing research about projections and matrices really blew my mind and
** made me think of my senses differently. (i know, im a drama queen) so.
** because of this, this comment is going to be loooonnnng, and i will break
** it up into two parts. in [PART 1] it will just be about the code.
** [PART 2] is where i'll blab on about why why i found this project so
** impactful.
*/

/*
**                              [PART 1]
** there are two types of projections i did for this project, orthographic
** projection, and perspective projection. what projections are, are a
** flattening of 3D information, into a 2D visual information.
**
** orthographic projection a type of parallel projection where the information
** is projected directly on a cartesian plane without geometrical distortion.
** visually, it is kind of like an mri machine where each image is taken at a
** layer at a time, and then stacked on top of each other. (this is not exactly
** right but whatever) the math for this is easy (i found out during this
** project this is what linear algebra is), because all we need to do is discard
** the z information, which the drawing algorithm naturally does because
** only the x and y infomation is used. the important part is the order of
** transformations(done via matrices). we need to move it to the origin, where
** we will then apply the rotations. otherwise, our rotation will be janky
** and our project, while not technically wrong, will look like crap. we then
** scale and then translate it to the center of the screen/window. then, we
** project it. functionally, i didnt need to put in the orthogration function
** for the orthographic view to work, because rotation will imbue the x and y
** with z information and give a 3D view, but i decided to keep it in to
** preserve the process.
*/
/*
** the perspective, on the other hand, is really much more complicated, and
** i kind of lucked onto finding a visually correct way of it. (i stil feel like
** my understanding of matrices is not good enough) perspective projection
** is a way to represent in 2D how we actually see the world in our eyes.
** objects that are closer are bigger, objects farther away are smaller.
** this happens because, unlike orthographic projection, we are receiving
** information about the world from one view point, instead of from the
** point where the information is at. (we stand here, look at a tree,
** interpret that information, instead of going up to it and taking measurments)
** the rotation and move onto the origin is the same as the previous view,
** but now, the x and y have to decrease according to how far away it is.
** however, once that is calculated, the process of translating and scaling
** it is the same.
*/
/*
**                              [PART 2]
** what makes this project so special for me is it made me think about what 3D
** information actually is. it also made me ponder the methods in which we,
** as humans, sense, process, and interpret information taken through our
** senses, and flatten it into something that we understand. many thoughts
** came about throughout this project.
**
** 1) all information that comes through our eyes are 2D information. it is
** our previous experiences of space and happening 4D experiences that
** lets our brain process these information into 3D understanding. For
** example, when we look at a sculpture, we are only sensing 2D visual
** information about it. we might interpret 3D'ness from it, because of
** perspective where we would take into account other object's positionality,
** or because we know its a sculpture and it's supposed to be 3D. if we
** were to move around it though, we would be traveling through space,
** and viewing 2Dimages of it, and integrating that with out 4D experience
** of the object. --to be continued later, gotta turn in project--
*/

void	calculate_proj(t_map *mastermap)
{
	move_to_origin(mastermap);
	rotation_z(mastermap);
	rotation_y(mastermap);
	rotation_x(mastermap);
	if (!mastermap->perspective)
	{
		scalation(mastermap);
		translation(mastermap);
	}
	if (mastermap->perspective)
	{
		perspection(mastermap);
		scalation(mastermap);
		translation(mastermap);
	}
	else
		orthogration(mastermap);
}
