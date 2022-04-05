/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_highlight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:47:56 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 22:00:53 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculates the dot product of the light ray and the camera ray for
** the point of intersection to see if a specular highlight is created.
** The math for reflection vector is
** r = l - 2(l * n) n
** where r is reflection vector, l is the light dir, and n is the normal
** of the point of intersection. Since specular highlight depends on the angle
** at which the observer/camera looks at it, its intensity is calculated
** is = il(r * v)^alpha
** where is is the incident intensity for spec, il is the incident intensity
** of the light, r is the reflection vector and v is the camera vector. Alpha
** is a constant; in this case the shininess of the material itself.
*/
static double	get_dot_product(t_ray lray, t_ray camray, t_point this)
{
	t_vec	l;
	t_vec	r;
	t_vec	v;

	l = lray.dir;
	r = ft_vec_sub(l, ft_vec_scale(this.normal,
				(ft_vec_dot(l, this.normal) * 2.0)));
	ft_vec_normalise(&r);
	v = camray.dir;
	ft_vec_normalise(&v);
	return (ft_vec_dot(r, v));
}

/*
** Generates a light ray from the current poi to light. Note that the change to
** the light ray's start point is to counteract shadow acne by adding
** a near-neglible value to the start point into the direction of the light.
*/
static t_ray	gen_lray(t_vec lpos, t_point *this)
{
	t_vec	ldir;
	t_vec	start;
	t_ray	lray;

	ldir = ft_vec_sub(lpos, this->poi);
	ft_vec_normalise(&ldir);
	start = ft_vec_add(this->poi, ft_vec_scale(ldir, 0.001));
	lray = ray_gen(start, ft_vec_add(start, ldir));
	return (lray);
}

/*
** Loops through all objects in a scene to see if they block the current
** light; if not, returns a calculated intensity for the shine.
*/
static double	check_intensity(t_scene *s, t_point *this, t_ray ray, int obj)
{
	t_ray	lray;
	t_point	new;
	double	dot_product;
	double	intensity;
	int		i;

	intensity = 0.0;
	init_point(&new);
	lray = gen_lray(s->lights[s->at_light].pos, this);
	i = 0;
	while (i < s->objcount)
	{
		if (s->objs[i].get_t(lray, s->objs[i], &new))
			return (0.0);
		i++;
	}
	dot_product = get_dot_product(lray, ray, *this);
	if (dot_product > 0.0)
		intensity = s->objs[obj].reflectivity * pow(dot_product,
				s->objs[obj].shine);
	return (intensity);
}

/*
** Computes the specular highlight of a point. First loops through
** all lights in the scene, checking if they are blocked by objects
** and thus in shadow. If no valid intersection is found, a reflection
** ray will be computed and all valid lights will be added to this
** highlight.
*/
t_colour	mat_highlight(t_scene *s, t_point *this, t_ray ray, int obj)
{
	t_colour	spec;
	double		intensity;

	s->at_light = 0;
	init_colour(&spec);
	while (s->at_light < s->lcount)
	{
		if (s->lights[s->at_light].intensity)
		{
			intensity = check_intensity(s, this, ray, obj);
			if (intensity)
				colour_add_intensity(&spec,
					s->lights[s->at_light].colour, intensity);
		}
		s->at_light++;
	}
	return (spec);
}
