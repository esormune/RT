/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:22:51 by esormune          #+#    #+#             */
/*   Updated: 2022/03/15 14:59:56 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Initialises the camera struct.
*/
void	init_camera(t_camera *cam)
{
	ft_vec_init(&cam->pos);
	ft_vec_init(&cam->look_at);
	ft_vec_init(&cam->up);
	ft_vec_init(&cam->u);
	ft_vec_init(&cam->v);
	ft_vec_init(&cam->centre);
	ft_vec_init(&cam->alignment);
	cam->length = 1.0;
	cam->horizon = 0.25;
	cam->aspect_ratio = 16.0 / 9.0;
	cam->pos.y = -10;
	cam->pos.z = -2.0;
	cam->up.z = 1.0;
}

/*
** Updates camera geometry.
*/
void	camera_update(t_camera *cam)
{
	cam->alignment = ft_vec_sub(cam->look_at, cam->pos);
	ft_vec_normalise(&cam->alignment);
	if (cam->alignment.x == 0 && cam->alignment.y == 0 && cam->alignment.z == 1)
		ft_vec_set(&cam->up, 0.0, 1.0, 0.0);
	cam->u = ft_vec_cross(cam->alignment, cam->up);
	ft_vec_normalise(&cam->u);
	cam->v = ft_vec_cross(cam->u, cam->alignment);
	ft_vec_normalise(&cam->v);
	cam->centre = ft_vec_add(cam->pos,
			(ft_vec_scale(cam->alignment, cam->length)));
	cam->u = ft_vec_scale(cam->u, cam->horizon);
	cam->v = ft_vec_scale(cam->v, (cam->horizon / cam->aspect_ratio));
}
