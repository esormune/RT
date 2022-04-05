/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:26:44 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 21:12:52 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_colour	get_average(t_colour *set)
{
	t_colour	avg;
	int			i;

	i = 0;
	init_colour(&avg);
	while (i < 9)
	{
		avg.r += set[i].r;
		avg.g += set[i].g;
		avg.b += set[i].b;
		i++;
	}
	avg.r /= 9;
	avg.g /= 9;
	avg.b /= 9;
	return (avg);
}

static void	set_default(t_colour *set)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (set[i].r < 0)
			set[i] = set[0];
		i++;
	}
}

static void	set_colours(t_channels *c, t_colour *set, int at, double max)
{
	ft_memset(set, -1, sizeof(t_colour));
	ft_colour_fset(&set[0], c->r[at], c->g[at], c->b[at]);
	if ((at % c->w) != 0 && (at - 1) > 0)
		ft_colour_fset(&set[1], c->r[at - 1], c->g[at - 1], c->b[at - 1]);
	if ((at % (c->w - 1)) != 0 && (at + 1) < max)
		ft_colour_fset(&set[2], c->r[at + 1], c->g[at + 1], c->b[at + 1]);
	at -= c->w;
	if (at > 0)
	{
		ft_colour_fset(&set[3], c->r[at], c->g[at], c->b[at]);
		if ((at % c->w) != 0 && (at - 1) > 0)
			ft_colour_fset(&set[4], c->r[at - 1], c->g[at - 1], c->b[at - 1]);
		if ((at % (c->w - 1)) != 0 && (at + 1) < max)
			ft_colour_fset(&set[5], c->r[at + 1], c->g[at + 1], c->b[at + 1]);
	}
	at += (2 * c->w);
	if (at < max)
	{
		ft_colour_fset(&set[6], c->r[at], c->g[at], c->b[at]);
		if ((at % c->w) != 0 && (at - 1) > 0)
			ft_colour_fset(&set[7], c->r[at - 1], c->g[at - 1], c->b[at - 1]);
		if ((at % (c->w - 1)) != 0 && (at + 1) < max)
			ft_colour_fset(&set[8], c->r[at + 1], c->g[at + 1], c->b[at + 1]);
	}
	set_default(set);
}

/*
** Applies an antialiasing effect by taking the average of the pixel
** and its surrounding values.
*/
void	antialiasing_draw_image(t_img *img, t_channels *c)
{
	double		max_colour;
	t_colour	colours[9];
	int			x;
	int			y;
	int			at;

	y = 0;
	img->scene.max = find_max_colour(c);
	max_colour = calc_max(img->scene.max);
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			at = c->w * y + x;
			set_colours(c, colours, at, (WIN_H * WIN_W - 1));
			draw_pixel(x, y, img->win_buffer, \
					get_colour(img->scene.filter, get_average(colours), \
					max_colour));
			x++;
		}
		y++;
	}
}
