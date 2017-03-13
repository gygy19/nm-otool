/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:21:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:21:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

void			get_operand(t_ofile *ofile, char id)
{
	if (id == '0')
		get_operand_zero(ofile);
	else if (id == '1')
		;
}
