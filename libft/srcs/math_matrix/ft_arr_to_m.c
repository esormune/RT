/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_to_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:19:16 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:19:31 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a 4x4 matrix created from array.
*/
t_matrix	ft_arr_to_m(double *arr)
{
	t_matrix	out;
	int			i;
	int			j;
	int			k;

	j = 0;
	k = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			out.m[j][i] = arr[k];
			i++;
			k++;
		}
		j++;
	}
	return (out);
}
