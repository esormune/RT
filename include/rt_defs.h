/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:31:23 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 19:12:47 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFS_H
# define RT_DEFS_H

# define WIN_NAME "RT"
# define WIN_H 720
# define WIN_W 1280
# define NUM_THREADS 50

// shapes
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3

# define HALF_PI 1.5708
# define PI 3.1416//TODO either use this or M_PI
# define EPSILON 1e-6
# define IGNORE 100e6

//ray backwards and forwards transform flags
# define FWDTSFM 0
# define BWDTSFM 1

//parameter checks
# define SIZE_PARAMS 3
# define LIGHT_PARAMS 8
# define OBJ_PARAMS 21
# define CAM_PARAMS 4
# define CAM_PARAMS_LOOKAT 7
# define IMAGE_PARAMS 7
# define SCENE_PARAMS 6

//for reflections
# define MAX_RAYS 3

//texture disruptions
# define NONE 0
# define CHECKERS 1
# define WAVE 2
# define PERLIN 3
# define MARBLE 4
# define WOOD 5
# define CLOUD 6
# define RAINBOW 7

//filters, note that NONE applies here as well
# define BW 1
# define SEPIA 2
# define INVERSE 3
# define AA 4

//for bitmap writing
# define BYTES_PER_PIXEL 3//rgb
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

#endif
