/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_identity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:22:01 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:22:22 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a matrix to default (identity) matrix.
*/
void	ft_m_set_identity(t_matrix *m)
{
	ft_bzero(m, sizeof(t_matrix));
	m->m[0][0] = 1;
	m->m[1][1] = 1;
	m->m[2][2] = 1;
	m->m[3][3] = 1;
}
