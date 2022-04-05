/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_make_identity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:39 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:29:54 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Creates and returns an identity matrix.
*/
t_matrix	ft_m_make_identity(void)
{
	t_matrix	m;

	ft_bzero(&m, sizeof(t_matrix));
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}
