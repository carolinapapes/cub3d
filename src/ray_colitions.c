/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_colitions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:33:48 by capapes           #+#    #+#             */
/*   Updated: 2025/02/21 14:37:48 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
* @brief Get the angle of the player in radians
*
* The angle is saved in a static variable and is updated on each call;
* @param dir Rotation direction. 1 for clockwise, -1 for counter-clockwise;
* @return double The angle in radians
*/
double	get_angle(int dir)
{
	static double	angle;

	angle += dir * 0.01;
	if (angle >= 2.0)
		angle -= 2.0;
	else if (angle < 0.0)
		angle += 2.0;
	return (angle);
}

/*
* @brief returns the cordinates of the position 
* of the endpoint of the ray given a length relative to the player;
*
* [GRAPHIC REPRESENTATION] media/ray_colitions.png
* @param angle The angle of the ray (a);
* @param len The length of the ray (len);
* @return t_vector The coordinates of the end point of the ray (x, y);
*/
t_vector	get_direction_vector(int dir)
{
	t_vector	endpoint;
	double		angle;

	angle = get_angle(dir);
	endpoint.x = cos(angle * M_PI);
	endpoint.y = sin(angle * M_PI);
	return (endpoint);
}
