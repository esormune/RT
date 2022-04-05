/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:58:49 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 21:09:41 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculates and returns the max value from the image.
*/
double	calc_max(t_colour max)
{
	double	ret;

	ret = max.r;
	if (ret < max.g)
		ret = max.g;
	if (ret < max.b)
		ret = max.b;
	return (ret);
}

t_colour	find_max_colour(t_channels *c)
{
	uint		i;
	uint		size;
	t_colour	max;

	size = c->h * c->w;
	i = 0;
	max.r = 0;
	max.g = 0;
	max.b = 0;
	max.a = 1;
	while (i < size)
	{
		if (c->r[i] > max.r)
			max.r = c->r[i];
		if (c->g[i] > max.g)
			max.g = c->g[i];
		if (c->b[i] > max.b)
			max.b = c->b[i];
		i++;
	}
	return (max);
}
