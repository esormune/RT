/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_marble.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:55:13 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 20:55:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Adds a marble disruption to the colour, which is gotten by giving the pixel
** at position x, y (u, v) a colour = 255 * sin(x + y). By giving the x and y
** points factors you can change the angle and period, and by giving the sine
** a factor, you can add turbulence. X and Y period give the repetition in
** their respective directions. Turbulence power at 0 is a normal sine power,
** at != 0 makes twists of size turb_size.
*/
static float	marble(float x, float y)
{
	float		x_period;
	float		y_period;
	float		turb_power;
	float		turb_size;
	float		xy_value;

	x_period = 5.0;
	y_period = 10.0;
	turb_power = 5.0;
	turb_size = 32;
	xy_value = x * x_period / WIN_W + y * y_period / WIN_H + turb_power
		* turbulence(x, y, turb_size) / 256;
	return (fabs(sin(xy_value * PI)));
}

void	texture_marble(t_point *p)
{
	float		x;
	float		y;
	float		noise;

	x = (int)(round(((p->uv.u + 1.0) / 2) * (double)WIN_W));
	y = (double)WIN_H - ((int)(round(((p->uv.v + 1.0) / 2) * (double)WIN_H)));
	noise = marble(x, y);
	p->colour.r *= noise;
	p->colour.g *= noise;
	p->colour.b *= noise;
}
