/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:35 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 16:03:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets translation, rotation, and scaling aspects to a matrix.
*/
void	ft_m_transform(t_matrix *m, t_vec trans, t_vec rot, t_vec scale)
{
	t_matrix	tr;
	t_matrix	sc;
	t_matrix	rx;
	t_matrix	ry;
	t_matrix	rz;

	ft_m_translation(&tr, trans);
	ft_m_scale(&sc, scale);
	ft_m_rotate_x(&rx, rot);
	ft_m_rotate_y(&ry, rot);
	ft_m_rotate_z(&rz, rot);
	*m = ft_m_multiply(tr, rx);
	*m = ft_m_multiply(*m, ry);
	*m = ft_m_multiply(*m, rz);
	*m = ft_m_multiply(*m, sc);
}
