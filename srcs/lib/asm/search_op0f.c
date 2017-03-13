/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_op0f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:25:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:25:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

const struct s_instable	*search_op0f(t_ofile *ofile)
{
	unsigned char byte;

	ofile->length++;
	byte = get_value(sizeof(char), ofile->ptr, ofile->length);
	ofile->opcode4 = byte >> 4 & 0xf;
	ofile->opcode5 = byte & 0xf;
	if (ofile->opcode4 > 12)
	{
		ft_asprintf(&ofile->sasm, ".byte 0x%01x%01x, 0x%01x%01x #bad opcode\n",
			(unsigned int)ofile->opcode1, (unsigned int)ofile->opcode2,
			(unsigned int)ofile->opcode4, (unsigned int)ofile->opcode5);
		return (&op0f[1][0]);
	}
	return (&op0f[ofile->opcode4][ofile->opcode5]);
}
