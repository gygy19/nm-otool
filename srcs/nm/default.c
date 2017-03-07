/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:36:08 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/07 17:36:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	search_syms(char *file, void *map, int is_64)
{
	void						*header;
	uint32_t					i;
	struct load_command			*cmd;
	void						*ptr;

	header = map;
	i = 0;
	(void)file;
	if (is_64 == 1)
	{
		ptr = CASTHEADER_X64 + HEADER_OFFSET;
		swap_mach_header_64(CASTHEADER_X32);
	}
	else
	{
		ptr = CASTHEADER_X32 + HEADER_OFFSET;
		swap_mach_header_32(CASTHEADER_X32);
	}
	while (WHILE_CMDS)
	{
		cmd = (struct load_command*)ptr;
		if (is_64 == 1)
			parse_sym64(cmd, ptr, map);
		else
			parse_sym32(cmd, ptr, map);
		ptr += cmd->cmdsize;
		i++;
	}
}
