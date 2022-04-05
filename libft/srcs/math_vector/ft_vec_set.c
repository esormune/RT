/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:47:47 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets points to a vector.
*/
void	ft_vec_set(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
