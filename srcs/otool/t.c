/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:20:05 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:20:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	parse_segment(void *header, struct load_command *cmd,\
		void *ptr, int is_64)
{
	struct section_64			*section;

	if (IS_SEGMENT_X64 && IS_X64)
	{
		section = ptr + SIZE_SEG;
		if (IS_SEGTEXT)
			print_section_text(section, CASTHEADER_X64);
	}
	else if (IS_SEGMENT_X32 && IS_X32)
	{
		section = ptr + SIZE_SEG;
		if (IS_SEGTEXT)
			print_section_text(section, CASTHEADER_X32);
	}
}

void	search_segement__text(char *file, void *map, int is_64)
{
	void						*header;
	uint32_t					i;
	struct load_command			*cmd;
	void						*ptr;

	header = map;
	i = 0;
	ft_printf("%s:\n", file);
	if (is_64 == 1)
	{
		ptr = CASTHEADER_X64 + HEADER_OFFSET;
	}
	else
	{
		ptr = CASTHEADER_X32 + HEADER_OFFSET;
		swap_mach_header_32(CASTHEADER_X32);
	}
	while (WHILE_CMDS)
	{
		cmd = (struct load_command*)ptr;
		parse_segment(header, cmd, ptr, is_64);
		ptr += cmd->cmdsize;
		i++;
	}
}
