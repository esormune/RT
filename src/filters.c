/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:54:33 by esormune          #+#    #+#             */
/*   Updated: 2022/03/27 17:25:58 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Converts rgb channel data with a balanced max value into a uint32_t.
*/
uint32_t	convert_colour(double r, double g, double b, double max)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	uint32_t		colour;

	red = (unsigned char)((r / max) * 255.0);
	green = (unsigned char)((g / max) * 255.0);
	blue = (unsigned char)((b / max) * 255.0);
	colour = ft_colour(red, green, blue);
	return (colour);
}

/*
** Inverts rgb channel data with a balanced max value into a uint32_t
** inverse colour.
*/
uint32_t	filter_inverse(double r, double g, double b, double max)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	uint32_t		colour;

	red = (unsigned char)((r / max) * 255.0);
	green = (unsigned char)((g / max) * 255.0);
	blue = (unsigned char)((b / max) * 255.0);
	colour = ft_colour(red, green, blue);
	colour = 0XFFFFFF - colour;
	return (colour);
}

/*
** Converts rgb channel data with a balanced max value into a weighted
** luminosity black and white uint32_t colour.
*/
uint32_t	filter_bw(double r, double g, double b, double max)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				bw;
	uint32_t		colour;

	red = (unsigned char)(((r / max) * 255.0));
	green = (unsigned char)(((g / max) * 255.0));
	blue = (unsigned char)(((b / max) * 255.0));
	bw = ft_clamp_d((red * 0.3) + (green * 0.59) + (blue * 0.11), 0, 255);
	colour = ft_colour(bw, bw, bw);
	return (colour);
}

/*
** Converts rgb channel data with a balanced max value into a
** sepia tone uint32_t colour.
*/
uint32_t	filter_sepia(double r, double g, double b, double max)
{
	t_8colour	orig;
	t_8colour	sepia;
	uint32_t	colour;

	orig.r = (unsigned char)(((r / max) * 255.0));
	orig.g = (unsigned char)(((g / max) * 255.0));
	orig.b = (unsigned char)(((b / max) * 255.0));
	sepia.r = (unsigned char)(0.393 * orig.r + 0.769 * orig.g + 0.189 * orig.b);
	sepia.g = (unsigned char)(0.349 * orig.r + 0.686 * orig.g + 0.168 * orig.b);
	sepia.b = (unsigned char)(0.272 * orig.r + 0.534 * orig.g + 0.131 * orig.b);
	sepia.r = ft_clamp_d(sepia.r, 0, 255);
	sepia.g = ft_clamp_d(sepia.g, 0, 255);
	sepia.b = ft_clamp_d(sepia.b, 0, 255);
	colour = ft_colour(sepia.r, sepia.g, sepia.b);
	return (colour);
}

/*
** Applies the desired filter and returns a uint32_t colour.
** If no filter, converts colour normally.
*/
uint32_t	get_colour(int filter, t_colour og, double max)
{
	uint32_t	new;

	if (filter == BW)
		new = filter_bw(og.r, og.g, og.b, max);
	else if (filter == SEPIA)
		new = filter_sepia(og.r, og.g, og.b, max);
	else if (filter == INVERSE)
		new = filter_inverse(og.r, og.g, og.b, max);
	else
		new = convert_colour(og.r, og.g, og.b, max);
	return (new);
}
