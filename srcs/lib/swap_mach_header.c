/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_mach_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:43:25 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/01 19:43:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	swap_mach_header_32(struct mach_header *mh)
{
	mh->magic = ft_osswapconstint32(mh->magic);
	mh->cputype = ft_osswapconstint32(mh->cputype);
	mh->cpusubtype = ft_osswapconstint32(mh->cpusubtype);
	mh->filetype = ft_osswapconstint32(mh->filetype);
	mh->ncmds = ft_osswapconstint32(mh->ncmds);
	mh->sizeofcmds = ft_osswapconstint32(mh->sizeofcmds);
	mh->flags = ft_osswapconstint32(mh->flags);
}

void	swap_mach_header_64(struct mach_header *mh)
{
	mh->magic = ft_osswapconstint32(mh->magic);
	mh->cputype = ft_osswapconstint32(mh->cputype);
	mh->cpusubtype = ft_osswapconstint32(mh->cpusubtype);
	mh->filetype = ft_osswapconstint32(mh->filetype);
	mh->ncmds = ft_osswapconstint32(mh->ncmds);
	mh->sizeofcmds = ft_osswapconstint32(mh->sizeofcmds);
	mh->flags = ft_osswapconstint32(mh->flags);
}
