/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:05:40 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:08:26 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Parses filter.
*/
static int	parse_filter(char *str)
{
	str = ft_toupper_str(str);
	if (ft_strcmp(str, "NONE") == 0)
		return (NONE);
	else if (ft_strcmp(str, "BW") == 0)
		return (BW);
	else if (ft_strcmp(str, "SEPIA") == 0)
		return (SEPIA);
	else if (ft_strcmp(str, "INVERSE") == 0)
		return (INVERSE);
	else if (ft_strcmp(str, "AA") == 0)
		return (AA);
	return (NONE);
}

/*
** Parses the extra scene variables from the scene file.
*/

void	parse_scene(char **words, t_scene *s, t_flags *flags)
{
	int	max;

	flags->scene++;
	if (flags->scene != 1)
		ft_getout("Too many scene descriptors.");
	max = ft_arr_size(words);
	if (max != SCENE_PARAMS)
		ft_getout("Invalid scene parameters.");
	s->filter = parse_filter(words[1]);
	s->ambient.intensity = ft_clamp_d(ft_atof(words[2]), 0.0, 10);
	s->ambient.intensity /= 100;
	ft_vec_init(&s->ambient.pos);
	colour_fset_clamp(&s->ambient.colour, ft_atof(words[3]),
		ft_atof(words[4]), ft_atof(words[5]));
}
