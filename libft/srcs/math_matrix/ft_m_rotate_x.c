/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_rotate_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:17:26 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:31:56 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets an x rotation matrix.
*/
void	ft_m_rotate_x(t_matrix *m, t_vec rot)
{
	ft_m_set_identity(m);
	m->m[1][1] = cos(rot.x);
	m->m[1][2] = -sin(rot.x);
	m->m[2][1] = sin(rot.x);
	m->m[2][2] = cos(rot.x);
}
