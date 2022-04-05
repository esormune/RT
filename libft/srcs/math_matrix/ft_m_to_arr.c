/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:19:51 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:19:59 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Turns a matrix into an array.
*/
void	ft_m_to_arr(t_matrix m, double *arr)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			arr[k] = m.m[j][i];
			i++;
			k++;
		}
		j++;
	}
}
