/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desable_opcode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:36:41 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:36:43 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

static void	desable_suffix_name(t_ofile *ofile)
{
	if (ofile->dp->adr_mode != CBW && ofile->dp->adr_mode != CWD)
	{
		if (ofile->dp->suffix)
		{
			if (ofile->data16 == true)
				ft_asprintf(&ofile->sasm, "%sl", ofile->dp->name);
			else
				ft_asprintf(&ofile->sasm, "%sq", ofile->dp->name);
		}
		else
			ofile->sasm = NULL;
	}
}

char		*desable_opcode(t_ofile *ofile, size_t size)
{
	ofile->sasm = NULL;
	if (ofile->length > size)
		return (NULL);
	if (ofile->dp->indirect == (const struct s_instable *)op0f)
		ofile->dp = search_op0f(ofile);
	ofile->got_modrm_byte = false;
	if (ofile->dp->indirect != TERM)
		ofile->dp = search_opfp(ofile);
	if (ofile->dp->indirect != TERM)
	{
		ft_asprintf(&ofile->sasm,\
			".byte 0x%02x #bad opcode", (unsigned int)ofile->byte);
		ofile->sasm = NULL;
	}
	desable_suffix_name(ofile);
	if (ofile->sasm != NULL)
		switch_commands(ofile);
	return (ofile->sasm);
}
