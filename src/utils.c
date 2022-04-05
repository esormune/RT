/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:10 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 23:53:19 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Checks whether or not two floating point numbers are
** within a close enough range defined by the machine epsilon.
*/
t_bool	close_enough(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (TRUE);
	return (FALSE);
}

/*
** Turns degrees to radians.
*/
double	d_to_rad(int deg)
{
	double	clamp;

	clamp = ft_clamp_d(deg, 0, 360);
	return (clamp * (PI / 180.0f));
}

void	print_vec_nl(t_vec v)
{
	ft_printf("%.3lf\n%.3lf\n%.3lf\n", v.x, v.y, v.z);
}

void	print_colour_as_vec(t_colour c)
{
	ft_printf("colour: %.3lf\n%.3lf\n%.3lf\n", c.r, c.g, c.b);
}

/*
** Prints a 3x3 matrix.
*/
void	m3_print(t_m3 m)
{
	int	i;
	int	j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			ft_printf("%f ", m.m[j][i]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}
