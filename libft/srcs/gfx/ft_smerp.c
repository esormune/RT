/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smerp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:45:13 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 15:45:23 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Smooth interpolation. TODO move to libft
*/
float	ft_smerp(float start, float end, float perc)
{
	return (ft_lerp(start, end, (perc * perc * (3 - 2 * perc))));
}
