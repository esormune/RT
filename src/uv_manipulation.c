/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_manipulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:55:37 by esormune          #+#    #+#             */
/*   Updated: 2022/03/20 14:24:30 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Applies a transform matrix to a uv point.
*/
void	m3_apply_tform(t_m3 m, t_uv *uv)
{
	t_vec	temp;
	t_vec	ret;

	temp.x = uv->u;
	temp.y = uv->v;
	temp.z = 0;
	ret = m3_multiply_vec(m, temp);
	uv->u = ret.x;
	uv->v = ret.y;
}

static void	uv_set_trans(t_m3 *m, t_uv trans)
{
	m3_set_identity(m);
	m->m[0][2] = trans.u;
	m->m[1][2] = trans.v;
}

static void	uv_set_rot(t_m3 *m, double rot)
{
	m3_set_identity(m);
	m->m[0][0] = cos(rot);
	m->m[0][1] = -sin(rot);
	m->m[1][0] = sin(rot);
	m->m[1][1] = cos(rot);
}

static void	uv_set_scale(t_m3 *m, t_uv scale)
{
	m3_set_identity(m);
	m->m[0][0] = scale.u;
	m->m[1][1] = scale.v;
}

/*
** Transform matrices for a 2d UV map.
*/
void	uv_transform(t_m3 *tform, t_uv trans, double rot, t_uv scale)
{
	t_m3	tr;
	t_m3	r;
	t_m3	sc;

	uv_set_trans(&tr, trans);
	uv_set_rot(&r, rot);
	uv_set_scale(&sc, scale);
	*tform = m3_multiply(tr, r);
	*tform = m3_multiply(*tform, sc);
}
