/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:23:07 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:07:17 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	Colors the pixel in given coordinates of the given buffer as the given
*	hexadecimal value [0xAARRGGBB]. (00 for AA being zero transparency)
*/
void	draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color)
{
	uint32_t	i;

	i = (buf->w * y) + x;
	if (x < buf->w && y < buf->h)
		buf->px[i] = color;
}

static void	draw(t_img *thread)
{
	t_colour	rgb;
	uint		x;
	uint		y;
	int			at;

	y = thread->nb;
	while (y < thread->max_nb)
	{
		x = 0;
		while (x < WIN_W)
		{
			at = thread->channels->w * y + x;
			ft_colour_fset(&rgb, thread->channels->r[at],
				thread->channels->g[at], thread->channels->b[at]);
			draw_pixel(x, y, thread->win_buffer, \
					get_colour(thread->scene.filter, rgb, thread->max_color));
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

static void	join_threads(pthread_t *thr)
{
	size_t	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
}

/*
** Gets max value from the rgb channels, then loops through all the
** pixels and gets the channel values, converting the colours
** a uint32_t, saving that onto the window buffer.
*/
void	draw_image(t_img *img, t_channels *c)
{
	pthread_t	thr[NUM_THREADS];
	t_img		thread[NUM_THREADS];
	int			rc;
	int			i;

	if (img->scene.filter == AA)
		return (antialiasing_draw_image(img, img->channels));
	img->scene.max = find_max_colour(c);
	img->max_color = calc_max(img->scene.max);
	i = 0;
	while (i < NUM_THREADS)
	{
		thread[i] = *img;
		thread[i].nb = (WIN_H - 1) / NUM_THREADS * i;
		thread[i].max_nb = (WIN_H - 1) / NUM_THREADS * (i + 1);
		rc = pthread_create(&thr[i], NULL, (void *(*)(void *))draw,
				(void *)&thread[i]);
		if (rc)
			exit(1);
		i++;
	}
	join_threads(thr);
}

/*
** Copies drawn image buffer into the pixels to be displayed by
** the SDL library.
*/
void	draw_img_to_window(t_img *img)
{
	if (SDL_LockTexture(img->win_tex, NULL, \
		&img->win_pixels, &img->win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(img->win_pixels, img->win_buffer->px, \
			WIN_H * img->win_pixel_pitch);
	SDL_UnlockTexture(img->win_tex);
	if (SDL_RenderCopy(img->rend, img->win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(img->rend);
}
