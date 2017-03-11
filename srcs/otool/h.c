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

void	print_header_64(t_ofile *ofile)
{
	ft_printf("Mach header\n");
	ft_printf(" %10s cputype cpusubtype  caps    ", "magic");
	ft_printf("filetype ncmds sizeofcmds      flags\n");
	ft_printf(" %#10x %8d %10d %#10x  %5d %5d %10d %0#.8x\n",\
		ofile->swap(ofile, ofile->mh64->magic),\
		ofile->swap(ofile, ofile->mh64->cputype), 3,\
		ofile->swap(ofile, ofile->mh64->cpusubtype) & CPU_SUBTYPE_MASK,\
		ofile->swap(ofile, ofile->mh64->filetype),\
		ofile->swap(ofile, ofile->mh64->ncmds),\
		ofile->swap(ofile, ofile->mh64->sizeofcmds),\
		ofile->swap(ofile, ofile->mh64->flags));
}

void	print_header_32(t_ofile *ofile)
{
	ft_printf("Mach header\n");
	ft_printf(" %10s cputype cpusubtype  caps    ", "magic");
	ft_printf("filetype ncmds sizeofcmds      flags\n");
	ft_printf(" %#10x %8d %10d %#10x  %5d %5d %10d %0#.8x\n",\
		ofile->swap(ofile, ofile->mh->magic),\
		ofile->swap(ofile, ofile->mh->cputype), 3,\
		ofile->swap(ofile, ofile->mh->cpusubtype) & CPU_SUBTYPE_MASK,\
		ofile->swap(ofile, ofile->mh->filetype),\
		ofile->swap(ofile, ofile->mh->ncmds),\
		ofile->swap(ofile, ofile->mh->sizeofcmds),\
		ofile->swap(ofile, ofile->mh->flags));
}
