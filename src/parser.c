/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:01 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 14:07:56 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Parses the size of arrays from the char array.
*/
static void	parse_sizes(char **words, t_scene *scene)
{
	scene->objcount = ft_atoi(words[0]);
	if (scene->objcount <= 0 || scene->objcount > 15)
		ft_getout("Bad number of objects.");
	scene->lcount = ft_atoi(words[1]);
	if (scene->lcount <= 0 || scene->lcount > 5)
		ft_getout("Bad number of lights.");
	scene->imgcount = ft_atoi(words[2]);
	if (scene->imgcount < 0 || scene->imgcount > 10)
		ft_getout("Bad number of images.");
}

/*
** Parses the first lines into object count, light count, and image count.
*/
int	parse_beginning(int fd, t_scene *scene)
{
	char	**words;
	char	*f;
	int		x;
	int		max;

	x = get_next_line(fd, &(f));
	if (f == NULL)
		ft_getout("Empty file.");
	if (f[0] != '#' || x <= 0)
		ft_getout("Invalid file.");
	free(f);
	x = get_next_line(fd, &(f));
	if (f[0] == '#' || x <= 0)
		ft_getout("Invalid file.");
	words = ft_strsplit(f, 9);
	max = ft_arr_size(words);
	if (max != 3)
		ft_getout("Invalid file.");
	parse_sizes(words, scene);
	free(f);
	ft_free_array(words);
	return (0);
}

/*
** Initialises the memory allocation for the scene struct
** after parsing the first line.
*/
static void	init_scene(t_scene *scene)
{
	scene->objs = ft_calloc(scene->objcount, sizeof(t_obj));
	if (!scene->objs)
		ft_getout("Failure to allocate objects.");
	scene->lights = ft_calloc(scene->lcount, sizeof(t_light));
	if (!scene->lights)
		ft_getout("Failure to allocate lights.");
	if (scene->imgcount)
	{
		scene->imgs = ft_calloc(scene->imgcount, sizeof(t_image));
		if (!scene->imgs)
			ft_getout("Failure to allocate images.");
	}
	init_camera(&scene->camera);
	camera_update(&scene->camera);
}

/*
** Loops through the file and saves objects, lights,
** camera points. Any invalid text will invalidate file.
** First row is a comment, second has to have obj count
** & light count.
*/
int	parse_file(int fd, t_scene *scene, t_flags *flags)
{
	char	*f;
	int		x;

	while (1)
	{
		x = get_next_line(fd, &(f));
		if (x == 0)
			break ;
		if (x < 0)
			ft_getout("Open failure.");
		if (ft_strcmp(f, "") == 0)
			ft_getout("Invalid file.");
		parse_line(f, scene, flags);
		free(f);
	}
	if (flags->objs != scene->objcount || flags->lights != scene->lcount \
		|| flags->images != scene->imgcount)
		ft_getout("Invalid amount of lights, objects, and/or images.");
	return (0);
}

/*
** Begins parsing the file.
*/
void	parser(t_scene *scene, char *str)
{
	t_flags	flags;
	int		fd;
	int		ret;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_getout("Cannot open file.");
	scene->at_light = 0;
	scene->at_obj = 0;
	scene->at_img = 0;
	ret = parse_beginning(fd, scene);
	if (ret != 0)
		ft_getout("Invalid file.");
	init_scene(scene);
	ft_bzero(&flags, sizeof(t_flags));
	ret = parse_file(fd, scene, &flags);
	if (ret != 0)
		ft_getout("Invalid file.");
}
