/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:12 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 18:31:21 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Sets the rgb values for the channels.
*/
static void	set_pixel(t_img *img, uint32_t x, uint32_t y, t_colour c)
{
	uint32_t	i;

	if (x > img->channels->w || y > img->channels->h)
		return ;
	i = (img->channels->w * y) + x;
	img->channels->r[i] = c.r;
	img->channels->g[i] = c.g;
	img->channels->b[i] = c.b;
}

static void	set_closest(t_scene *scene, int *closest_obj, int current_obj)
{
	*closest_obj = current_obj;
	scene->closest.poi = scene->current.poi;
	scene->closest.normal = scene->current.normal;
	scene->closest.colour = scene->objs[current_obj].colour;
	scene->closest.uv = scene->current.uv;
}

/*
** Uses a ray from the camera into the pixel point and checks
** for an intersection with any objects in the scene.
*/
static t_bool	check_intersect(t_img *img, t_ray ray, int *closest_obj)
{
	int		i;
	double	min_dist;
	double	dist;
	t_bool	does_intersect;

	i = 0;
	does_intersect = FALSE;
	min_dist = 1e6;
	while (i < img->scene.objcount)
	{
		if (img->scene.objs[i].get_t(ray, img->scene.objs[i],
				&img->scene.current))
		{
			does_intersect = TRUE;
			dist = ft_vec_magn(ft_vec_sub(img->scene.current.poi, ray.start));
			if (dist < min_dist)
			{
				min_dist = dist;
				set_closest(&img->scene, closest_obj, i);
			}
		}
		i++;
	}
	return (does_intersect);
}

/*
* Renders the portion of the image that was given to the thread.
* nb is the starting pixel coordinate, max_nb is the ending one.
*/
static void	trace(t_img *thread)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	int			closest_obj;

	y = thread->nb;
	while (y < thread->max_nb)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = ray_gen_cam(thread, x, y);
			if (check_intersect(thread, ray, &closest_obj))
			{
				thread->scene.raycount = 0;
				if (compute_colour(&thread->scene, &thread->scene.closest,
						ray, closest_obj))
					set_pixel(thread, x, y, thread->scene.closest.colour);
			}
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

/*
** Creates threads and divides the screen buffer into as many portions
** as there are threads. Exits upon failure to create threads.
** Joins threads and renders image.
*/
void	render(t_img *img)
{
	pthread_t	thr[NUM_THREADS];
	t_img		thread[NUM_THREADS];
	int			rc;
	int			i;

	i = 0;
	while (i < NUM_THREADS)
	{
		thread[i] = *img;
		thread[i].nb = (WIN_H - 1) / NUM_THREADS * i;
		thread[i].max_nb = (WIN_H - 1) / NUM_THREADS * (i + 1);
		rc = pthread_create(&thr[i], NULL, (void *(*)(void *))trace,
				(void *)&thread[i]);
		if (rc)
			exit(1);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
	draw_image(img, img->channels);
}
