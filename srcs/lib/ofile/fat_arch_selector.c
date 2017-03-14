/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:05:33 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/14 17:05:35 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

struct fat_arch	*select_fat_arch_i386(t_ofile *ofile, int nfat, int current)
{
	ofile->arch32 = ofile->map + sizeof(struct fat_header)\
		+ (sizeof(struct fat_arch) * current);
	if (ofile->swap(ofile, ofile->arch32->cputype) == CPU_TYPE_I386)
		return (ofile->arch32);
	current++;
	if (current >= nfat)
		return (NULL);
	return (select_fat_arch_i386(ofile, nfat, current));
}

struct fat_arch	*select_fat_arch_x86_64(t_ofile *ofile, int nfat, int current)
{
	ofile->arch64 = ofile->map + sizeof(struct fat_header)\
		+ (sizeof(struct fat_arch) * current);
	if (ofile->swap(ofile, ofile->arch64->cputype) == CPU_TYPE_X86_64)
		return (ofile->arch64);
	current++;
	if (current >= nfat)
		return (NULL);
	return (select_fat_arch_x86_64(ofile, nfat, current));
}
