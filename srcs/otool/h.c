/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:19:58 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:19:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	printheader_infos(void *map)
{
	struct mach_header	*header;

	header = map;
	ft_printf("Mach header\n");
	ft_printf(" %10s cputype cpusubtype  caps    ", "magic");
	ft_printf("filetype ncmds sizeofcmds      flags\n");
	ft_printf(" %#10x %8d %10d %#10x  %5d %5d %10d %0#.8x\n",\
		header->magic, header->cputype, 3,\
		header->cpusubtype & CPU_SUBTYPE_MASK,\
		header->filetype, header->ncmds,\
		header->sizeofcmds, header->flags);
}
