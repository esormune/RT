/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:46:29 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Vector cross product.
*/
t_vec	ft_vec_cross(t_vec a, t_vec b)
{
	t_vec	x;

	x.x = a.y * b.z - a.z * b.y;
	x.y = a.z * b.x - a.x * b.z;
	x.z = a.x * b.y - a.y * b.x;
	return (x);
}
