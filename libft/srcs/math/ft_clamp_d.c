/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:46:30 by esormune          #+#    #+#             */
/*   Updated: 2022/04/05 20:46:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_clamp_d(double value, double min, double max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}
