/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_set_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:21:29 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:21:51 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets element in 4x4 matrix.
*/
void	ft_m_set_value(t_matrix *m, int row, int column, double value)
{
	if (column > 4 || column < 0 || row > 4 || row < 0)
		return ;
	m->m[row][column] = value;
}
