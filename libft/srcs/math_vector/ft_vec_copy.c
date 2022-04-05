/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:47:34 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies vector.
*/
void	ft_vec_copy(t_vec *from, t_vec *to)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
}
