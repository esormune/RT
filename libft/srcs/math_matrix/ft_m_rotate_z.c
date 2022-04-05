/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_rotate_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:31 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:51 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a z rotation matrix.
*/
void	ft_m_rotate_z(t_matrix *m, t_vec rot)
{
	ft_m_set_identity(m);
	m->m[0][0] = cos(rot.z);
	m->m[0][1] = -sin(rot.z);
	m->m[1][0] = sin(rot.z);
	m->m[1][1] = cos(rot.z);
}
