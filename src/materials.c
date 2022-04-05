/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:50:42 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:07:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO add basic materials? Like a default metal etc.

/*
** A function to modify colour. Used for calculating transparency and
** reflection resulting colours. The formula is as follows:
** base = (mod_colour * quality) + (base * (1 - quality))
*/
static t_colour	modify_colour(t_colour base, t_colour mod, double quality)
{
	t_colour	new;

	new.r = (mod.r * quality) + (base.r * (1 - quality));
	new.g = (mod.g * quality) + (base.g * (1 - quality));
	new.b = (mod.b * quality) + (base.b * (1 - quality));
	return (new);
}

/*
** Adds two colours together.
*/
static t_colour	add_colours(t_colour a, t_colour b)
{
	t_colour	new;

	new.r = a.r + b.r;
	new.g = a.g + b.g;
	new.b = a.b + b.b;
	return (new);
}

/*
** Modifies base colour if shininess, reflection, or transparency
** needs to be calculated.
*/
static t_colour	compute_materials(t_scene *s, t_point *this, t_ray ray, int obj)
{
	t_colour	base;
	t_colour	refl;
	t_colour	spec;
	t_colour	refr;
	t_point		orig;

	orig = *this;
	base = this->colour;
	if (s->objs[obj].reflectivity > 0.0)
	{
		refl = mat_reflection(s, this, ray, obj);
		base = modify_colour(base, refl, s->objs[obj].reflectivity);
	}
	if (s->objs[obj].transparency > 0.0)
	{
		refr = mat_refraction(s, this, ray, obj);
		base = modify_colour(base, refr, s->objs[obj].transparency);
	}
	if (s->objs[obj].shine > 0.0)
	{
		spec = mat_highlight(s, &orig, ray, obj);
		base = add_colours(base, spec);
	}
	return (base);
}

/*
** Computes the colour for a material. Checks for shininess, reflectivity,
** and transparency. Returns a T/F based on if there is illumination
** on an object and therefore cause to colour the pixel.
*/
t_bool	compute_colour(t_scene *s, t_point *this, t_ray ray, int obj)
{
	t_colour	base;
	t_bool		illumination;

	illumination = light_check(s, this, obj);
	if (!illumination)
		return (FALSE);
	if (s->objs[obj].reflectivity > 0.0 || \
		s->objs[obj].transparency > 0.0 || \
		s->objs[obj].shine > 0.0)
	{
		base = compute_materials(s, this, ray, obj);
	}
	else
		base = this->colour;
	this->colour = base;
	return (TRUE);
}
