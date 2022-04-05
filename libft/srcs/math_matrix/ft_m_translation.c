/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:15:47 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a translation matrix.
*/
void	ft_m_translation(t_matrix *m, t_vec trans)
{
	ft_m_set_identity(m);
	m->m[0][3] = trans.x;
	m->m[1][3] = trans.y;
	m->m[2][3] = trans.z;
}
