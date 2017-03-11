/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_osswap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:38:07 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/01 19:38:09 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

uint32_t		ft_osswapconstint16(t_ofile *ofile, uint16_t x)
{
	if (ofile->is_swap == false)
		return (x);
	return ((((uint16_t)(x) & 0xff00) >> 8) |\
	(((uint16_t)(x) & 0x00ff) << 8));
}

uint32_t		ft_osswapconstint32(t_ofile *ofile, uint32_t x)
{
	if (ofile->is_swap == false)
		return (x);
	return (((((uint32_t)(x) & 0xff000000) >> 24) |\
	(((uint32_t)(x) & 0x00ff0000) >> 8) |\
	(((uint32_t)(x) & 0x0000ff00) << 8) |\
	(((uint32_t)(x) & 0x000000ff) << 24)));
}

uint32_t		ft_osswapconstint64(t_ofile *ofile, uint64_t x)
{
	if (ofile->is_swap == false)
		return (x);
	return ((((uint64_t)(x) & 0xff00000000000000ULL) >> 56) |\
	(((uint64_t)(x) & 0x00ff000000000000ULL) >> 40) |\
	(((uint64_t)(x) & 0x0000ff0000000000ULL) >> 24) |\
	(((uint64_t)(x) & 0x000000ff00000000ULL) >> 8) |\
	(((uint64_t)(x) & 0x00000000ff000000ULL) << 8) |\
	(((uint64_t)(x) & 0x0000000000ff0000ULL) << 24) |\
	(((uint64_t)(x) & 0x000000000000ff00ULL) << 40) |\
	(((uint64_t)(x) & 0x00000000000000ffULL) << 56));
}
