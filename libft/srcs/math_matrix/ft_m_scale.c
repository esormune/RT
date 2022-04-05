/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:16:23 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:18 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a scaling matrix.
*/
void	ft_m_scale(t_matrix *m, t_vec scale)
{
	ft_m_set_identity(m);
	m->m[0][0] = scale.x;
	m->m[1][1] = scale.y;
	m->m[2][2] = scale.z;
}
