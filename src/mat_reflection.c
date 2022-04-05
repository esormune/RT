/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_reflection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:45:49 by esormune          #+#    #+#             */
/*   Updated: 2022/03/16 22:04:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_closest(t_scene s, t_point *closest, t_point current, int obj)
{
	closest->poi = current.poi;
	closest->normal = current.normal;
	closest->colour = s.objs[obj].colour;
	closest->uv = current.uv;
}

/*
** Casts a reflection ray onto the scene, very much like the original
** function to check for intersections.
*/
static t_bool	check_intersect(t_scene *s, t_point *closest,
	int *closest_obj, int cur_obj)
{
	int		i;
	double	min_dist;
	double	dist;
	t_bool	does_intersect;
	t_point	current;

	i = 0;
	does_intersect = FALSE;
	min_dist = 1e6;
	while (i < s->objcount)
	{
		if (i != cur_obj && s->objs[i].get_t(s->r_ray, s->objs[i], &current))
		{
			does_intersect = TRUE;
			dist = ft_vec_magn(ft_vec_sub(current.poi, s->r_ray.start));
			if (dist < min_dist)
			{
				min_dist = dist;
				*closest_obj = i;
				set_closest(*s, closest, current, i);
			}
		}
		i++;
	}
	return (does_intersect);
}

/*
** Creates a reflection ray from current poi. The added scale of 0.001 dir
** is to counteract self-intersection.
*/
t_ray	r_ray_gen(t_ray ray, t_point current)
{
	t_ray	r_ray;
	t_vec	start;
	t_vec	v;
	t_vec	r;

	start = ft_vec_add(current.poi, ft_vec_scale(ray.dir, 0.001));
	v = ray.dir;
	r = ft_vec_sub(v, ft_vec_scale(current.normal,
				(ft_vec_dot(v, current.normal) * 2.0)));
	r_ray = ray_gen(start, ft_vec_add(start, r));
	return (r_ray);
}

/*
** Computes the reflection of an object. Reflection is calculated
** by the formula of
** r = v - 2 (v * n)n
** where r reflection vector, v is the original ray dir (here from camera)
** and n is the normal of the point of intersection/point of reflection.
** Calls onto itself recursively until MAX_RAYS is reached. Initialises
** the colour to black, and will return that if an intersection is found
** but the object is not lit; otherwise the closest point will store the colour.
** Returns the colour of this closest object.
*/
t_colour	mat_reflection(t_scene *s, t_point *current, t_ray ray, int obj)
{
	t_colour	r_colour;
	t_point		closest;
	t_bool		does_intersect;
	int			closest_obj;

	init_colour(&r_colour);
	s->r_ray = r_ray_gen(ray, *current);
	does_intersect = check_intersect(s, &closest, &closest_obj, obj);
	if (does_intersect && s->raycount < MAX_RAYS)
	{
		s->raycount++;
		if (compute_colour(s, &closest, s->r_ray, closest_obj))
			r_colour = closest.colour;
	}
	return (r_colour);
}
