/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_rotate_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:18:08 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:00 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a y rotation matrix.
*/
void	ft_m_rotate_y(t_matrix *m, t_vec rot)
{
	ft_m_set_identity(m);
	m->m[0][0] = cos(rot.y);
	m->m[0][2] = sin(rot.y);
	m->m[2][0] = -sin(rot.y);
	m->m[2][2] = cos(rot.y);
}
