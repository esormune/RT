/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:23:02 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:11:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Nulls a colour struct.
*/
void	init_colour(t_colour *c)
{
	c->r = 0.0;
	c->g = 0.0;
	c->b = 0.0;
	c->a = 0.0;
}

/*
** Sets a colour struct with rgb values where
** they are limited between 0.0 and 1.0.
*/
void	colour_fset_clamp(t_colour *c, double r, double g, double b)
{
	c->r = ft_clamp_d(r, 0.0, 1.0);
	c->g = ft_clamp_d(g, 0.0, 1.0);
	c->b = ft_clamp_d(b, 0.0, 1.0);
	c->a = 0.0;
}

/*
** Adds an intensity of colour b onto colour a. Used for example when
** adding specular highlights or adding specific colours from lights
** onto a base colour.
*/
void	colour_add_intensity(t_colour *a, t_colour b, double i)
{
	a->r += (b.r * i);
	a->g += (b.g * i);
	a->b += (b.b * i);
}

/*
** Checks for colour max values. If any of the new colours
** are higher than what's already saved, will set the values
** as the new ones.
*/
void	colour_check_max(t_colour *max, t_colour c)
{
	if (c.r > max->r)
		max->r = c.r;
	if (c.g > max->g)
		max->g = c.g;
	if (c.b > max->b)
		max->b = c.b;
}

/*
** Sets the correct colour for the point of intersection by checking
** if the object has an image or a texture as well as if the scene
** has ambient lighting.
*/
void	colour_at_poi(t_scene *s, t_point *closest, int obj, t_colour c)
{
	t_bool	is_light;

	is_light = TRUE;
	if (!c.r && !c.g && !c.b)
		is_light = FALSE;
	if (s->objs[obj].has_image >= 0 && s->objs[obj].has_image < s->imgcount)
		image_texture(closest, &s->imgs[s->objs[obj].has_image]);
	if (s->objs[obj].txt.type != NONE && s->objs[obj].txt.type != WAVE)
		texture_sort(closest, &s->objs[obj].txt);
	if ((c.r || c.g || c.b) || (!is_light && !s->ambient.intensity))
		ft_colour_fset(&closest->colour, (closest->colour.r * c.r), \
			(closest->colour.g * c.g), (closest->colour.b * c.b));
	else if (s->ambient.intensity)
		ft_colour_fset(&closest->colour, (closest->colour.r * 0.001), \
			(closest->colour.g * 0.001), (closest->colour.b * 0.001));
	if (s->ambient.intensity)
		ambient_add(s->ambient, closest);
}
