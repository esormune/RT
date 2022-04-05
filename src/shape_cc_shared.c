/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cc_shared.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:16 by esormune          #+#    #+#             */
/*   Updated: 2022/03/21 23:22:43 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Contains functions that are used by both
** cone and cylinder calculations with minor
** differences.
*/

/*
** Sets uv points for possible use when the poi is on the circumference
** of the cone or cylinder.
*/
static void	set_uv_area(t_point *p, int object)
{
	double	x;
	double	y;
	double	z;

	x = p->poi.x;
	y = p->poi.y;
	z = p->poi.z;
	p->uv.u = atan2(y, x) / M_PI;
	if (object == CONE)
		p->uv.v = (z * 2.0) + 1.0;
	else
		p->uv.v = z;
}

void	cc_calc_t(t_quadratic q, double *t, t_vec v, t_ray ray)
{
	if (q.sqroot > 0.0)
	{
		t[0] = (-q.b + q.sqroot) / (2.0 * q.a);
		t[1] = (-q.b - q.sqroot) / (2.0 * q.a);
	}
	else
	{
		t[0] = IGNORE;
		t[1] = IGNORE;
	}
	if (close_enough(v.z, 0.0))
	{
		t[2] = IGNORE;
		t[3] = IGNORE;
	}
	else
	{
		t[2] = (ray.start.z - 1.0) / -v.z;
		t[3] = (ray.start.z + 1.0) / -v.z;
	}
}

void	cc_calc_poi(t_vec *poi, double *t, t_vec v, t_ray ray)
{
	if (t[0] != IGNORE)
	{
		poi[0] = ft_vec_add(ray.start, ft_vec_scale(v, t[0]));
		poi[1] = ft_vec_add(ray.start, ft_vec_scale(v, t[1]));
	}
	if (t[2] != IGNORE)
	{
		poi[2] = ft_vec_add(ray.start, ft_vec_scale(v, t[2]));
		poi[3] = ft_vec_add(ray.start, ft_vec_scale(v, t[3]));
	}
}

t_bool	cc_area_intersect(t_obj obj, t_point *p)
{
	t_vec	org_normal;
	t_vec	obj_origin;

	set_uv_area(p, obj.shape);
	ft_vec_init(&obj_origin);
	m_apply_vec(&obj_origin, obj.tform);
	if (obj.shape == CYLINDER)
		ft_vec_set(&org_normal, p->poi.x, p->poi.y, 0.0);
	else
	{
		ft_vec_set(&org_normal, p->poi.x, p->poi.y,
			(-sqrtf(pow(p->poi.x, 2.0) + pow(p->poi.y, 2.0))));
	}
	p->normal = m3_multiply_vec(obj.ltform, org_normal);
	m_apply_vec(&p->poi, obj.tform);
	if (obj.txt.type == WAVE)
		texture_wave(p, obj.txt);
	ft_vec_normalise(&p->normal);
	return (TRUE);
}

t_bool	cc_base_intersect(t_obj obj, t_point *p)
{
	t_vec	org_normal;
	t_vec	obj_origin;

	p->uv.u = p->poi.x;
	p->uv.v = p->poi.y;
	ft_vec_init(&obj_origin);
	m_apply_vec(&obj_origin, obj.tform);
	if (obj.shape == CYLINDER)
		ft_vec_set(&org_normal, 0.0, 0.0, p->poi.z);
	else
		ft_vec_set(&org_normal, 0.0, 0.0, 1.0);
	p->normal = m3_multiply_vec(obj.ltform, org_normal);
	m_apply_vec(&p->poi, obj.tform);
	if (obj.txt.type == WAVE)
		texture_wave(p, obj.txt);
	ft_vec_normalise(&p->normal);
	return (TRUE);
}
