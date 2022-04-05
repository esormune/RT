/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m3_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:44 by esormune          #+#    #+#             */
/*   Updated: 2022/03/19 20:55:01 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Transposes a  3x3 matrix.
*/
t_m3	m3_transpose(t_m3 m3)
{
	t_m3	transpose;
	int		i;
	int		j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			transpose.m[j][i] = m3.m[i][j];
			i++;
		}
		j++;
	}
	return (transpose);
}

/*
** Multiplies a 3x1 vector by a 3x3 matrix.
*/
t_vec	m3_multiply_vec(t_m3 m, t_vec v)
{
	t_vec	ret;

	ret.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2];
	ret.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2];
	ret.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2];
	return (ret);
}

/*
** Performs matrix multiplication for 2 3x3 matrices.
*/
t_m3	m3_multiply(t_m3 ma, t_m3 mb)
{
	t_m3	ret;
	int		column;
	int		row;

	column = 0;
	while (column < 3)
	{
		row = 0;
		while (row < 3)
		{
			ret.m[row][column] = \
			ma.m[row][0] * mb.m[0][column] + \
			ma.m[row][1] * mb.m[1][column] + \
			ma.m[row][2] * mb.m[2][column];
			row++;
		}
		column++;
	}
	return (ret);
}

/*
** Makes a 3x3 matrix into an identity matrix.
*/
void	m3_set_identity(t_m3 *m3)
{
	ft_bzero(m3, sizeof(t_m3));
	m3->m[0][0] = 1;
	m3->m[1][1] = 1;
	m3->m[2][2] = 1;
}

/*
** Extracts the linear portion of a 4x4 matrix into a 3x3 matrix.
*/
t_m3	m3_linear(t_matrix m4)
{
	t_m3	m3;
	int		row;
	int		column;

	row = 0;
	while (row < 3)
	{
		column = 0;
		while (column < 3)
		{
			m3.m[row][column] = m4.m[row][column];
			column++;
		}
		row++;
	}
	m3 = m3_inverse(m3);
	m3 = m3_transpose(m3);
	return (m3);
}
