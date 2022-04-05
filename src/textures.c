/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:51 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:04:58 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculates turbulence. Size is the initial zoom. The final result
** is normalised to be between 0 - 255. A size of 256 gets a nice
** smooth cloudiness. The division by 256 places the noise from
** the hash into the 0 - 1 range.
*/
float	turbulence(float x, float y, float size)
{
	float	orig_size;
	float	value;

	value = 0.0;
	orig_size = size;
	while (size >= 1)
	{
		value += ft_noise(x / size, y / size) / 256 * size;
		size /= 2.0;
	}
	return (128.0 * value / orig_size);
}

/*
** Sorts into the appropriate function for getting texture disruption.
*/
void	texture_sort(t_point *p, t_texture *txt)
{
	if (txt->type == CHECKERS)
		texture_checkers(p, txt);
	else if (txt->type == PERLIN)
		texture_perlin(p);
	else if (txt->type == MARBLE)
		texture_marble(p);
	else if (txt->type == CLOUD)
		texture_cloud(p);
	else if (txt->type == WOOD)
		texture_wood(p);
	else if (txt->type == RAINBOW)
		texture_rainbow(p);
}
