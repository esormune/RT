/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_normed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:43:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/22 00:23:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a normalised copy of a vector instead of normalising
** vector in place.
*/
t_vec	ft_vec_normed(t_vec v)
{
	t_vec	ret;
	double	w;

	ret = v;
	w = ft_vec_magn(ret);
	if (w > 0)
	{
		ret.x /= w;
		ret.y /= w;
		ret.z /= w;
	}
	return (ret);
}
