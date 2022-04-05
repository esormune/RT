/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_multiply_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:27 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:30:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Calculates 4x4 matrix by 1x4 vector.
*/
t_vec4	ft_m_multiply_vec(t_matrix m, t_vec4 v)
{
	t_vec4	ret;

	ret.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] \
	+ v.w * m.m[0][3];
	ret.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] \
	+ v.w * m.m[1][3];
	ret.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] \
	+ v.w * m.m[2][3];
	ret.w = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * m.m[3][2] \
	+ v.w * m.m[3][3];
	return (ret);
}
