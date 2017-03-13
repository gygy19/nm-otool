/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:36:59 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:37:01 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

int		switch_commands(t_ofile *ofile)
{
	if (ofile->dp->adr_mode == BSWAP)
		return (asm_bswap(ofile));
	if (ofile->dp->adr_mode == XINST)
		return (asm_xinst(ofile));
	if (ofile->dp->adr_mode == MV)
		return (asm_mv(ofile));
	if (ofile->dp->adr_mode == RMW)
		return (asm_rmw(ofile));
	if (ofile->dp->adr_mode == R)
		return (asm_r(ofile));
	ofile->sasm = NULL;
	return (1);
}
