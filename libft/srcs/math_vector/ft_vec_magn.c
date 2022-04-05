/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_magn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:48:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Vector magnitude / length of vector.
*/
double	ft_vec_magn(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
