/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:07:42 by esormune          #+#    #+#             */
/*   Updated: 2022/03/20 14:03:45 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Sets a UV vector.
*/
void	set_uv(t_uv *uv, double u, double v)
{
	uv->u = u;
	uv->v = v;
}

/*
** Hack function for handling textures. TODO make txt pointer function?
*/
void	set_texture(t_texture *t, int txt)
{
	if (txt == CHECKERS)
	{
		set_uv(&t->trans, 0.0, 0.0);
		set_uv(&t->scale, 10.0, 10.0);
		t->rot = 0.0;
	}
	else
	{
		set_uv(&t->trans, 0.0, 0.0);
		set_uv(&t->scale, 1.0, 1.0);
		t->rot = 0.0;
	}
	uv_transform(&t->tform, t->trans, t->rot, t->scale);
}

/*
** Parses the texture information.
*/
int	parse_texture(char *str)
{
	str = ft_toupper_str(str);
	if (ft_strcmp(str, "NONE") == 0)
		return (0);
	else if (ft_strcmp(str, "CHECKERS") == 0)
		return (1);
	else if (ft_strcmp(str, "WAVE") == 0)
		return (2);
	else if (ft_strcmp(str, "PERLIN") == 0)
		return (3);
	else if (ft_strcmp(str, "MARBLE") == 0)
		return (4);
	else if (ft_strcmp(str, "WOOD") == 0)
		return (5);
	else if (ft_strcmp(str, "CLOUD") == 0)
		return (6);
	else if (ft_strcmp(str, "RAINBOW") == 0)
		return (7);
	return (0);
}
