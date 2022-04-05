/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:47:54 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 16:48:26 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_noise(int x, int y)
{
	static int	g_hash[] = {208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24,
		140, 71, 48, 140, 254, 245, 255, 247, 247, 40, 185, 248, 251, 245, 28,
		124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202, 224, 245, 128, 167,
		204, 9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 100, 108,
		167, 44, 43, 77, 180, 204, 8, 81, 70, 223, 11, 38, 24, 254, 210, 210,
		177, 32, 81, 195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13, 203, 9,
		47, 104, 125, 117, 114, 124, 165, 203, 181, 235, 193, 206, 70, 180, 174,
		0, 167, 181, 41, 164, 30, 116, 127, 198, 245, 146, 87, 224, 149, 206,
		57, 4, 192, 210, 65, 210, 129, 240, 178, 105, 228, 108, 245, 148, 140,
		40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62, 3, 237, 55,
		89, 232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17, 212, 203, 149,
		152, 140, 187, 234, 177, 73, 174, 193, 100, 192, 143, 97, 53, 145, 135,
		19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 39, 145, 101, 120, 99,
		3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42, 30, 154, 120,
		67, 87, 167, 135, 176, 183, 191, 253, 115, 184, 21, 233, 58, 129, 233,
		142, 39, 128, 211, 118, 137, 139, 255, 114, 20, 218, 113, 154, 27, 127,
		246, 250, 1, 8, 198, 250, 209, 92, 222, 173, 21, 88, 102, 219};
	int			temp;

	temp = g_hash[(y + NOISE_SEED) % 256];
	temp = g_hash[(temp + x) % 256];
	return (temp);
}

/*
** Adds noise based on the coordinates given.
** First separates the fraction and the int values of
** the coordinates to use as a percentage in the
** interpolation. Stores the added noise value in a 4 point vector
** where the noise is calculated from a grid then forms.
** Gets an interpolation between the bottoms
** and the tops of the grid, then at last between the
** bottom and top.
*/
static float	interpolate(t_vec4 grid, float x_frac, float y_frac)
{
	float	low;
	float	high;
	float	res;

	low = ft_smerp(grid.x, grid.y, x_frac);
	high = ft_smerp(grid.z, grid.w, x_frac);
	res = ft_smerp(low, high, y_frac);
	return (res);
}

float	ft_noise(float x, float y)
{
	t_vec4	grid;
	int		x_int;
	int		y_int;
	float	x_frac;
	float	y_frac;

	x_int = (int)x;
	y_int = (int)y;
	x_frac = x - x_int;
	y_frac = y - y_int;
	grid.x = get_noise(x_int, y_int);
	grid.y = get_noise(x_int + 1, y_int);
	grid.z = get_noise(x_int, y_int + 1);
	grid.w = get_noise(x_int + 1, y_int + 1);
	return (interpolate(grid, x_frac, y_frac));
}
