/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:26:03 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:09:38 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Adds an ambient light to a point of intersection on an object.
** Ambience is calculated by the ambient colour times the intensity
** times the colour of the object. Has clamping at the end to make
** sure any colour does not exceed the 0.0 - 1.0 range.
*/
void	ambient_add(t_light amb, t_point *p)
{
	t_colour	l;

	l.r = amb.colour.r * amb.intensity;
	l.g = amb.colour.g * amb.intensity;
	l.b = amb.colour.b * amb.intensity;
	p->colour.r += l.r;
	p->colour.g += l.g;
	p->colour.b += l.b;
	p->colour.r = ft_clamp_d(p->colour.r, 0.0, 1.0);
	p->colour.g = ft_clamp_d(p->colour.g, 0.0, 1.0);
	p->colour.b = ft_clamp_d(p->colour.b, 0.0, 1.0);
}
