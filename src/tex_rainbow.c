/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_rainbow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:04:12 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:04:23 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Makes a rainbow texture / colour disruption where the colour
** is set by the normal of the point.
*/
void	texture_rainbow(t_point *p)
{
	float	x;
	float	y;
	float	z;

	x = ((p->normal.x + 1.0) / 2);
	y = ((p->normal.y + 1.0) / 2);
	z = ((p->normal.z + 1.0) / 2);
	p->colour.r = x;
	p->colour.g = y;
	p->colour.b = z;
}
