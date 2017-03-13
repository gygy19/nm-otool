/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bswap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:31:03 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:31:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

int		asm_bswap(t_ofile *ofile)
{
	const char *reg_name;

	reg_name = g_reg32[(ofile->opcode5 & 0x7)][1];
	ft_asprintf(&ofile->sasm, "%s\t%s", ofile->sasm, reg_name);
	return (1);
}
