/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_cloud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:02:38 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:02:58 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	texture_cloud(t_point *p)
{
	uint32_t	x;
	uint32_t	y;
	t_hsl		hsl;
	uint8_t		light;

	x = (int)(round(((p->uv.u + 1.0) / 2) * (double)WIN_W));
	y = (double)WIN_H - ((int)(round(((p->uv.v + 1.0) / 2) * (double)WIN_H)));
	hsl.h = 240;
	hsl.s = 1;
	light = 169 + (uint8_t)(turbulence(x, y, 64)) / 4;
	hsl.l = (double)(light) / 255;
	p->colour = ft_hsl_to_rgb(hsl);
}
