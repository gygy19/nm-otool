/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modrm_byte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:18:32 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:18:34 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	modrm_byte(unsigned long *mode, unsigned long *reg,\
	unsigned long *r_m, unsigned char byte)
{
	*r_m = byte & 0x7;
	*reg = byte >> 3 & 0x7;
	*mode = byte >> 6 & 0x3;
}
