/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:57 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 21:13:32 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Sets an object's get_t function to the correct one.
*/
static void	set_t(t_obj *obj)
{
	if (obj->shape == SPHERE)
		obj->get_t = (void *)&sphere_t;
	else if (obj->shape == PLANE)
		obj->get_t = (void *)&plane_t;
	else if (obj->shape == CYLINDER)
		obj->get_t = (void *)&cylinder_t;
	else if (obj->shape == CONE)
		obj->get_t = (void *)&cone_t;
	else
		ft_getout("Invalid object.");
}

/*
** Sets an object's type. If not a valid string, exits as error.
*/
static void	set_obj_type(char *str, t_scene *s)
{
	if (ft_strcmp(str, "sphere") == 0)
		s->objs[s->at_obj].shape = SPHERE;
	else if (ft_strcmp(str, "plane") == 0)
		s->objs[s->at_obj].shape = PLANE;
	else if (ft_strcmp(str, "cylinder") == 0)
		s->objs[s->at_obj].shape = CYLINDER;
	else if (ft_strcmp(str, "cone") == 0)
		s->objs[s->at_obj].shape = CONE;
	else
		ft_getout("Invalid object given.");
}

static void	set_neg(t_scene *s, char *str)
{
	str = ft_toupper_str(str);
	if (ft_strcmp(str, "YES") == 0)
	{
		s->objs[s->at_obj].transparency = 1.0;
		s->objs[s->at_obj].ior = 1.0;
		s->objs[s->at_obj].reflectivity = 0.0;
		s->objs[s->at_obj].shine = 0.0;
		s->objs[s->at_obj].is_neg = TRUE;
	}
	else
		s->objs[s->at_obj].is_neg = FALSE;
}

/*
** Part 2 for object parsing.
*/
static void	parse_cont(char **words, t_scene *s)
{
	colour_fset_clamp(&s->objs[s->at_obj].colour, ft_atof(words[11]),
		ft_atof(words[12]), ft_atof(words[13]));
	ft_m_transform(&s->objs[s->at_obj].tform, s->objs[s->at_obj].trans,
		s->objs[s->at_obj].rot, s->objs[s->at_obj].scale);
	s->objs[s->at_obj].inv = ft_m_inverse(s->objs[s->at_obj].tform);
	s->objs[s->at_obj].ltform = m3_linear(s->objs[s->at_obj].tform);
	set_t(&s->objs[s->at_obj]);
	s->objs[s->at_obj].reflectivity = ft_clamp_d(ft_atof(words[14]), 0.0, 0.9);
	s->objs[s->at_obj].shine = ft_clamp_d(ft_atof(words[15]), 0, 50);
	s->objs[s->at_obj].transparency = ft_clamp_d(ft_atof(words[16]), 0.0, 1.0);
	s->objs[s->at_obj].ior = ft_clamp_d(ft_atof(words[17]), 0.1, 5.0);
	s->objs[s->at_obj].has_image = \
		(ft_clamp_d(ft_atoi(words[18]), 0, s->imgcount) - 1);
	s->objs[s->at_obj].txt.type = parse_texture(words[19]);
	if (s->objs[s->at_obj].txt.type != NONE)
		set_texture(&s->objs[s->at_obj].txt, s->objs[s->at_obj].txt.type);
	set_neg(s, words[20]);
	s->at_obj++;
}

/*
** Parses object information. TODO make some things cancel each other out?
*/
void	parse_object(char **words, t_scene *s, t_flags *flags)
{
	int	max;

	flags->objs++;
	if (flags->objs > s->objcount || s->at_obj >= s->objcount)
		ft_getout("Invalid number of objects.");
	max = ft_arr_size(words);
	if (max != OBJ_PARAMS)
		ft_getout("Invalid object parameters.");
	set_obj_type(words[1], s);
	ft_vec_set(&s->objs[s->at_obj].trans, ft_atof(words[2]),
		ft_atof(words[3]), ft_atof(words[4]));
	ft_vec_set(&s->objs[s->at_obj].rot, d_to_rad(ft_atoi(words[5])),
		d_to_rad(ft_atoi(words[6])), d_to_rad(ft_atoi(words[7])));
	ft_vec_set(&s->objs[s->at_obj].scale, ft_atof(words[8]),
		ft_atof(words[9]), ft_atof(words[10]));
	if (s->objs[s->at_obj].scale.x <= 0 || s->objs[s->at_obj].scale.y <= 0
		|| s->objs[s->at_obj].scale.z <= 0)
		ft_getout("Invalid object size.");
	return (parse_cont(words, s));
}
