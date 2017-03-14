/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_dp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:37:09 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:37:11 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

void		load_dp(t_ofile *ofile)
{
	ofile->data16 = false;
	ofile->addr16 = false;
	ofile->asmseg = "";
	while (true)
	{
		ofile->byte = get_value(sizeof(char), ofile->ptr, ofile->length);
		ofile->opcode1 = ofile->byte >> 4 & 0xf;
		ofile->opcode2 = ofile->byte & 0xf;
		ofile->dp = &asmtab[ofile->opcode1 % 16][ofile->opcode2 % 16];
		if (ofile->dp->adr_mode == PREFIX)
			ft_printf("%s\n", ofile->dp->name);
		else if (ofile->dp->adr_mode == AM)
			ofile->addr16 = !ofile->addr16;
		else if (ofile->dp->adr_mode == DM)
			ofile->data16 = !ofile->data16;
		else if (ofile->dp->adr_mode == OVERRIDE)
			ofile->asmseg = ofile->dp->name;
		else
			break ;
		ofile->length++;
	}
}
