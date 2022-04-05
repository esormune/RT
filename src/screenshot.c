/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:46:49 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:18:28 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Converts uint32_t colour to unsigned char rgb values.
*/
static void	colour_to_rgb_channels(t_uchar_rgb *cha, uint32_t *c)
{
	uint32_t	at;
	int			i;
	int			j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			at = WIN_W * j + i;
			cha->b[at] = (c[at] >> 16);
			cha->g[at] = (c[at] >> 8);
			cha->r[at] = c[at];
			i++;
		}
		j++;
	}
}

static int	channel_setup(t_uchar_rgb *c)
{
	c->r = ft_calloc(WIN_W * WIN_H, sizeof(unsigned char));
	c->g = ft_calloc(WIN_W * WIN_H, sizeof(unsigned char));
	c->b = ft_calloc(WIN_W * WIN_H, sizeof(unsigned char));
	if (!c->r || !c->g || !c->b)
		return (-1);
	return (0);
}

static void	channel_teardown(t_uchar_rgb *c)
{
	free(c->r);
	free(c->g);
	free(c->b);
}

/*
** Turns the rgb channels into an unsigned char array.
*/
static void	channels_to_image(t_uchar_rgb *c, \
		unsigned char image[WIN_H][WIN_W][BYTES_PER_PIXEL])
{
	int	i;
	int	j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			image[j][i][0] = (unsigned char)(c->r[i + j * WIN_W]);
			image[j][i][1] = (unsigned char)(c->g[i + j * WIN_W]);
			image[j][i][2] = (unsigned char)(c->b[i + j * WIN_W]);
			i++;
		}
		j++;
	}
}

/*
** Takes a screenshot of the image. Turns the rgb channels into
** an unsigned char array to then turn into a bitmap image.
*/
void	screenshot_image(t_img *img)
{
	unsigned char	image[WIN_H][WIN_W][BYTES_PER_PIXEL];
	t_uchar_rgb		c;
	char			name[100];

	bmp_name(name);
	if (name[0] == '\0')
		return (image_error("Screenshot name error."));
	if (channel_setup(&c) < 0)
		ft_getout("Malloc failure.");
	colour_to_rgb_channels(&c, img->win_buffer->px);
	channels_to_image(&c, image);
	create_bmp((unsigned char *)image, name);
	channel_teardown(&c);
}
