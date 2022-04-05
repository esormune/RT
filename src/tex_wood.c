/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_wood.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:51:35 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 20:54:30 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** xy_period marks the number of rings, turb_power the twists, and turb_size
** the turbulence size.
*/
static float	wood(float x, float y)
{
	float	xy_per;
	float	turb_power;
	float	turb_size;
	float	x2;
	float	y2;

	xy_per = 12.0;
	turb_power = 0.1;
	turb_size = 32;
	x2 = (x - 128 / 2) / 128;
	y2 = (y - 128 / 2) / 128;
	return (128.0 * fabs(sin(2 * xy_per * (sqrt(x2 * x2 + y2 * y2)
					+ turb_power * turbulence(x, y, turb_size) / 256.0) * PI)));
}

/*
** Texture for wood.
*/
void	texture_wood(t_point *p)
{
	uint8_t		r;
	uint8_t		g;
	float		x;
	float		y;
	float		noise;

	x = (int)(round(((p->uv.u + 1.0) / 2) * (double)WIN_W));
	y = (double)WIN_H - ((int)(round(((p->uv.v + 1.0) / 2) * (double)WIN_H)));
	noise = wood(x, y);
	r = (uint8_t)(80 + noise);
	g = (uint8_t)(30 + noise);
	p->colour.r = (double)r / 255;
	p->colour.g = (double)g / 255;
	p->colour.b = 30.0 / 255;
}
