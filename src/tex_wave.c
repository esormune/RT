/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_wave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:03:35 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:46:35 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Sine normale disruption for a wave effect.
*/
void	texture_wave(t_point *p, t_texture txt)
{
	double	new_rot;
	double	frequency;
	t_m3	new_tform;

	frequency = 50;
	new_rot = sin(p->uv.u * M_PI_2 * frequency);
	uv_transform(&new_tform, txt.trans, new_rot, txt.scale);
	p->normal = m3_multiply_vec(new_tform, p->normal);
}
