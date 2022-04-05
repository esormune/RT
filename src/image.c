/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:55:40 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 00:37:06 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	image_error(const char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

/*
** Loads and stores image data using the SDL bitmap reader.
** If there is a failure, will set "loaded" bool to false.
*/
void	image_load(const char *file, t_image *image)
{
	image->loaded = FALSE;
	image->surface = SDL_LoadBMP(file);
	if (!image->surface)
		return (image_error("Error loading the image."));
	image->w = image->surface->w;
	image->h = image->surface->h;
	image->pitch = image->surface->pitch;
	image->bpp = image->surface->format->BytesPerPixel;
	if (image->bpp != 4)
	{
		image->incorrect_bpp = TRUE;
		return (image_error("Incorrect image format."));
	}
	image->linesize = (image->pitch / image->bpp);
	image->size = image->h * image->linesize;
	SDL_LockSurface(image->surface);
	image->pixels = NULL;
	image->pixels = (uint32_t *)(image->surface->pixels);
	SDL_UnlockSurface(image->surface);
	image->loaded = TRUE;
}

/*
** Gets the colour for the intersection when he texture is an image.
** The point contains the uv map coordinates. If the image has
** failed to load, the colour will be set to a default one.
** Converts u and v into x and y ints; v and u are between -1 and 1
** so by adding 1 and then dividing by 2 we get numbers between 0 and 1.
** That's how we get the percentage of where it is on the uv map.
** Accounts for tiling.
*/
void	image_texture(t_point *p, t_image *i)
{
	t_uv		new;
	uint32_t	x;
	uint32_t	y;
	uint32_t	pixel;
	t_8colour	c;

	if (!i->loaded)
		ft_colour_fset(&p->colour, 1.0, 0.0, 1.0);
	else
	{
		new = p->uv;
		m3_apply_tform(i->tform, &new);
		x = (int)(round(((new.u + 1.0) / 2) * (double)i->w));
		y = i->h - ((int)(round(((new.v + 1.0) / 2) * (double)i->h)));
		x = ((x % i->w) + i->w) % i->w;
		y = ((y % i->h) + i->h) % i->h;
		if (x >= 0 && x < i->w && y >= 0 && y < i->h)
		{
			pixel = i->pixels[x + (y * i->linesize)];
			SDL_GetRGBA(pixel, i->surface->format, &c.r, &c.g, &c.b, &c.a);
			ft_colour_fset(&p->colour, ((double)c.r / 255.0),
				((double)c.g / 255.0), ((double)c.b / 255.0));
		}
	}
}
