/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:30:46 by capapes           #+#    #+#             */
/*   Updated: 2025/03/14 13:31:04 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_vector	vector_sum(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vector	set_components(double a, double b)
{
	t_vector	result;

	result.x = a;
	result.y = b;
	return (result);
}

t_vector	rectangle_vector(double a)
{
	t_vector	result;

	result.x = a;
	result.y = a;
	return (result);
}
