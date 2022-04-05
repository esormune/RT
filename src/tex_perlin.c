/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_perlin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:03:11 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:06:00 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculates a 2d perlin noise disruption.
*/
float	perlin(float x, float y, float freq, int depth)
{
	float	amp;
	float	res;
	float	div;
	int		i;

	x *= freq;
	y *= freq;
	amp = 1.0;
	res = 0.0;
	div = 0.0;
	i = 0;
	while (i < depth)
	{
		div += 256 * amp;
		res += ft_noise(x, y) * amp;
		amp /= 2;
		x *= 2;
		y *= 2;
		i++;
	}
	return (res / div);
}

/*
** Adds perlin noise disruption.
*/
void	texture_perlin(t_point *p)
{
	uint32_t	x;
	uint32_t	y;
	float		noise;

	x = (int)(round(((p->uv.u + 1.0) / 2) * (double)WIN_W));
	y = (double)WIN_H - ((int)(round(((p->uv.v + 1.0) / 2) * (double)WIN_H)));
	noise = perlin(x, y, 0.1, 4);
	noise = (noise + 1.0) / 2;
	p->colour.r = p->colour.r * noise;
	p->colour.g = p->colour.g * noise;
	p->colour.b = p->colour.b * noise;
}
