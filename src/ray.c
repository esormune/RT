/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:08 by esormune          #+#    #+#             */
/*   Updated: 2022/03/21 23:48:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Prints a ray.
*/
void	ray_print(t_ray ray)
{
	print_vec(ray.start);
	print_vec(ray.end);
	print_vec(ray.dir);
}

/*
** Copies a ray.
*/
void	ray_copy(t_ray *from, t_ray *to)
{
	ft_vec_copy(&from->start, &to->start);
	ft_vec_copy(&from->end, &to->end);
	ft_vec_copy(&from->dir, &to->dir);
}

/*
** Generates a ray from start point to end point.
*/
t_ray	ray_gen(t_vec start, t_vec end)
{
	t_ray	new;

	new.start = start;
	new.end = end;
	new.dir = ft_vec_sub(new.end, new.start);
	ft_vec_normalise(&new.dir);
	return (new);
}

/*
** Generates a ray from camera start to the pixel point given on
** screen space.
*/
t_ray	ray_gen_cam(t_img *img, int x, int y)
{
	t_ray	ray;
	t_vec	screen_point;
	t_vec	world_point;
	double	norm_x;
	double	norm_y;

	norm_x = (double)x * img->x_fact - 1.0;
	norm_y = (double)y * img->y_fact - 1.0;
	screen_point = ft_vec_add(img->scene.camera.centre,
			ft_vec_scale(img->scene.camera.u, norm_x));
	world_point = ft_vec_add(screen_point,
			ft_vec_scale(img->scene.camera.v, norm_y));
	ray.start = img->scene.camera.pos;
	ray.end = world_point;
	ray.dir = ft_vec_sub(ray.end, ray.start);
	return (ray);
}
