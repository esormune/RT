/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:14:13 by esormune          #+#    #+#             */
/*   Updated: 2022/02/21 16:14:43 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Prints a 4x4 matrix.
*/
void	ft_print_matrix(t_matrix m)
{
	int	i;
	int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			ft_printf("%f ", m.m[j][i]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}
