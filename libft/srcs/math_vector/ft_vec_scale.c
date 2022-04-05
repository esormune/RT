/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:48:45 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Vector scaling.
*/
t_vec	ft_vec_scale(t_vec a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	return (a);
}
