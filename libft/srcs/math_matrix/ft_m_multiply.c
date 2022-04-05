/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_multiply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:27 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:30:15 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Calculates a 4x4 matrix multiplication.
*/
t_matrix	ft_m_multiply(t_matrix ma, t_matrix mb)
{
	t_matrix	ret;
	int			column;
	int			row;

	column = 0;
	while (column < 4)
	{
		row = 0;
		while (row < 4)
		{
			ret.m[row][column] = \
			ma.m[row][0] * mb.m[0][column] + \
			ma.m[row][1] * mb.m[1][column] + \
			ma.m[row][2] * mb.m[2][column] + \
			ma.m[row][3] * mb.m[3][column];
			row++;
		}
		column++;
	}
	return (ret);
}
