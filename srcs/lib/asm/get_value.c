/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:16:36 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:16:37 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

unsigned long	get_value(unsigned long size, char *sect, unsigned long length)
{
	unsigned long i;
	unsigned long value;
	unsigned char byte;

	value = 0;
	i = 0;
	while (i < size)
	{
		byte = sect[length];
		value |= (unsigned long)byte << (8 * i);
		i++;
	}
	return (value);
}
