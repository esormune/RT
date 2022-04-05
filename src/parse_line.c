/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:34:21 by esormune          #+#    #+#             */
/*   Updated: 2022/03/18 20:34:36 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Parses given line and saves its data while checking validity.
** For the camera, will take in the most recent. 9 corresponds
** to tabs in the string split.
*/
void	parse_line(char *str, t_scene *scene, t_flags *flags)
{
	char	**words;

	if (str[0] == '#')
		return ;
	words = ft_strsplit(str, 9);
	if (!words)
		ft_getout("Failure in strsplit.");
	if (ft_strcmp(words[0], "camera") == 0)
		parse_camera(words, &scene->camera, flags);
	else if (ft_strcmp(words[0], "object") == 0)
		parse_object(words, scene, flags);
	else if (ft_strcmp(words[0], "light") == 0)
		parse_light(words, scene, flags);
	else if (ft_strcmp(words[0], "image") == 0)
		parse_image(words, scene, flags);
	else if (ft_strcmp(words[0], "scene") == 0)
		parse_scene(words, scene, flags);
	else
		ft_getout("Invalid file. Check starter word declarations.");
	ft_free_array(words);
}
