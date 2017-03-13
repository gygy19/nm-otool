/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_opfp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:25:51 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:25:58 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

static const struct s_instable	*send_opf_number(t_ofile *ofile)
{
	if (ofile->opcode2 == 0xB && ofile->mode == 0x3 && ofile->opcode3 == 4)
		return (&opfp5[ofile->r_m]);
	else if (ofile->opcode2 == 0xB && ofile->mode == 0x3 && ofile->opcode3 > 4)
	{
		ft_asprintf(&ofile->sasm,\
			".byte 0x%01x%01x, 0x%01x%01x 0x%02x #bad opcode\n",
			(unsigned int)ofile->opcode1, (unsigned int)ofile->opcode2,
			(unsigned int)ofile->opcode4, (unsigned int)ofile->opcode5,
			(unsigned int)ofile->byte);
		return (&op0f[1][0]);
	}
	else if (ofile->opcode2 == 0x9 && ofile->mode == 0x3 && ofile->opcode3 >= 4)
		return (&opfp4[ofile->opcode3 - 4][ofile->r_m]);
	else if (ofile->mode == 0x3)
		return (&opfp3[ofile->opcode2 - 8][ofile->opcode3]);
	else
		return (&opfp1n2[ofile->opcode2 - 8][ofile->opcode3]);
}

const struct s_instable			*search_opfp(t_ofile *ofile)
{
	ofile->got_modrm_byte = true;
	ofile->length++;
	ofile->byte = get_value(sizeof(char), ofile->ptr, ofile->length);
	modrm_byte(&ofile->mode,\
		(unsigned long *)&ofile->opcode3, &ofile->r_m, ofile->byte);
	if (ofile->opcode1 == 0xD && ofile->opcode2 >= 0x8)
		return (send_opf_number(ofile));
	return ((ofile->dp->indirect + ofile->opcode3));
}
