/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 22:43:50 by esormune          #+#    #+#             */
/*   Updated: 2022/03/19 21:42:00 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Parses images from the scene file into the image array.
** Sets the loaded value to false in the beginning and if there are
** any invalid parameters given, will not load image and exits function.
*/
void	parse_image(char **words, t_scene *s, t_flags *flags)
{
	int	max;

	flags->images++;
	if (flags->images > s->imgcount || s->at_img >= s->imgcount)
		ft_getout("Invalid number of images.");
	max = ft_arr_size(words);
	if (max != IMAGE_PARAMS)
		ft_getout("Invalid image parameters.");
	s->imgs[s->at_img].loaded = FALSE;
	s->imgs[s->at_img].incorrect_bpp = FALSE;
	uv_set(&s->imgs[s->at_img].trans, ft_atof(words[2]), ft_atof(words[3]));
	s->imgs[s->at_img].rot = d_to_rad(ft_atof(words[4]));
	uv_set(&s->imgs[s->at_img].scale, ft_atof(words[5]), ft_atof(words[6]));
	if (s->imgs[s->at_img].scale.u <= 0 || s->imgs[s->at_img].scale.v <= 0)
	{
		s->at_img++;
		return ;
	}
	uv_transform(&s->imgs[s->at_img].tform, s->imgs[s->at_img].trans,
		s->imgs[s->at_img].rot, s->imgs[s->at_img].scale);
	image_load(words[1], &s->imgs[s->at_img]);
	s->at_img++;
}
