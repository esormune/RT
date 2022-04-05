/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:44:45 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 15:45:02 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Linear interpolation algorithm. TODO move to libft
*/
float	ft_lerp(float start, float end, float percentage)
{
	return (start + (percentage * (end - start)));
}
