/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_refraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:56:25 by esormune          #+#    #+#             */
/*   Updated: 2022/03/27 17:23:04 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_closest(t_scene *scene, int *closest_obj, int current_obj)
{
	*closest_obj = current_obj;
	scene->closest.poi = scene->current.poi;
	scene->closest.normal = scene->current.normal;
	scene->closest.colour = scene->objs[current_obj].colour;
	scene->closest.uv = scene->current.uv;
}

static t_bool	check_intersect(t_scene *s, t_ray ray, int *closest_obj)
{
	int		i;
	double	min_dist;
	double	dist;
	t_bool	does_intersect;

	i = 0;
	does_intersect = FALSE;
	min_dist = 1e6;
	while (i < s->objcount)
	{
		if (s->objs[i].get_t(ray, s->objs[i], &s->current))
		{
			does_intersect = TRUE;
			dist = ft_vec_magn(ft_vec_sub(s->current.poi, ray.start));
			if (dist < min_dist)
			{
				min_dist = dist;
				set_closest(s, closest_obj, i);
			}
		}
		i++;
	}
	return (does_intersect);
}

static t_ray	refl_ray(t_point current, t_ray ray)
{
	t_ray	r_ray;
	t_vec	start;
	t_vec	v;
	t_vec	r;

	v = ray.dir;
	r = ft_vec_sub(v, ft_vec_scale(current.normal,
				(ft_vec_dot(v, current.normal) * 2.0)));
	start = ft_vec_add(current.poi, ft_vec_scale(r, 0.001));
	r_ray = ray_gen(start, ft_vec_add(start, r));
	return (r_ray);
}

static t_ray	form_ray(t_point *p, t_ray ray, double ior)
{
	t_vec	temp_normal;
	t_vec	ref_vec;
	double	c;
	t_ray	ret;

	ft_vec_normalise(&ray.dir);
	temp_normal = p->normal;
	c = ft_vec_dot(temp_normal, ray.dir) * (-1);
	if (c < 0.0)
	{
		temp_normal = ft_vec_scale(temp_normal, -1);
		c = ft_vec_dot(temp_normal, ray.dir) * (-1);
	}
	ref_vec = ft_vec_add(ft_vec_scale(ray.dir, ior),
			ft_vec_scale(temp_normal, (ior * c - sqrtf((1.0 - powf(ior, 2.0) * \
				(1.0 - powf(c, 2.0)))))));
	if (ref_vec.x != ref_vec.x)
		return (refl_ray(*p, ray));
	ret = ray_gen(ft_vec_add(p->poi, ft_vec_scale(ref_vec, 0.01)),
			ft_vec_add(p->poi, ref_vec));
	return (ret);
}

/*
** Calculates the refractive element of an object with transparency.
** The formula for the refractive vector is:
** RefV = rv + (rc - √ (1 - r^2(1 - c^2)))n
** where r = n1/n2
** c = cos01 = -n * v
** v = incident vector
** ior stands for the index of refraction. It is 1 for air, 1.33 for water,
** and 1.52 for glass.
** Forms two rays: one from the surface of the initial poi into the object,
** and checks whether that hits an intersection with the object's "exit".
** If not, this is the final ray to be used. Otherwise a new ray is calculated
** from that point of intersection.
** TODO make work with only one object that is transparent?
*/
t_colour	mat_refraction(t_scene *s, t_point *this, t_ray ray, int obj)
{
	t_colour	refr;
	t_ray		final;
	t_bool		does_intersect;
	t_point		new;
	int			closest_obj;

	init_colour(&refr);
	final = form_ray(this, ray, 1.0 / s->objs[obj].ior);
	does_intersect = s->objs[obj].get_t(final, s->objs[obj], &new);
	if (does_intersect)
	{
		final = form_ray(&new, final, s->objs[obj].ior);
		does_intersect = check_intersect(s, final, &closest_obj);
	}
	else
		does_intersect = check_intersect(s, final, &closest_obj);
	if (does_intersect)
	{
		compute_colour(s, &s->closest, final, closest_obj);
		refr = s->closest.colour;
	}
	return (refr);
}
