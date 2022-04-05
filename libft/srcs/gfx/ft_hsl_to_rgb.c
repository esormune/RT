/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsl_to_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:17:33 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 16:01:44 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	hue_to_rgb(float v1, float v2, float hue)
{
	if (hue < 0)
		hue += 1;
	if (hue > 1)
		hue -= 1;
	if (hue < (1.0 / 6))
		return (v1 + (v2 - v1) * 6 * hue);
	if (hue < (1.0 / 2))
		return (v2);
	if (hue < (2.0 / 3))
		return (v1 + (v2 - v1) * ((2.0f / 3) - hue) * 6);
	return (v1);
}

/*
** A function that turns hue/saturation/lightness into rgb.
** saturation and lightness should be between 0 and 1.
*/
t_colour	ft_hsl_to_rgb(t_hsl hsl)
{
	t_colour	c;
	double		v1;
	double		v2;
	double		hue;

	c.a = 0.0;
	if (hsl.s == 0)
		ft_colour_fset(&c, hsl.l, hsl.l, hsl.l);
	else
	{
		hue = (double)hsl.h / 360;
		if (hsl.l < 0.5)
			v2 = hsl.l * (1 + hsl.s);
		else
			v2 = (hsl.l + hsl.s) - (hsl.l * hsl.s);
		v1 = 2 * hsl.l - v2;
		c.r = hue_to_rgb(v1, v2, (hue + (1.0f / 3)));
		c.g = hue_to_rgb(v1, v2, hue);
		c.b = hue_to_rgb(v1, v2, (hue - (1.0f / 3)));
	}
	return (c);
}
