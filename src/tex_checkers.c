/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:04:44 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 21:04:56 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** A basic checkerboard texture for the objects. Takes in a t_point with the
** uv coordinates set, then uses the texture's transformation matrix to find
** the corresponding point on the texture, saves that into the poiints colour.
*/
void	texture_checkers(t_point *p, t_texture *txt)
{
	t_uv	new;
	int		at;

	new = p->uv;
	m3_apply_tform(txt->tform, &new);
	at = (int)floor(new.u) + (int)floor(new.v);
	if (at % 2 == 0)
		ft_colour_fset(&p->colour, 0.1, 0.1, 0.1);
}
