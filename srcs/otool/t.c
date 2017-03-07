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
		void *ptr, int flags)
{
	int							is_64;
	void						*section;

	is_64 = is_magic_64(get_magic(header));
	if (IS_SEGMENT_X64 && IS_X64)
	{
		section = ptr + SIZE_SEG;
		if ((ft_strcmp(((struct section_64*)section)->segname, "__TEXT") == 0))
			print_section_text(section, section, CASTHEADER_X64, flags);
	}
	else if (IS_SEGMENT_X32 && IS_X32)
	{
		section = ptr + SIZE_SEG;
		if ((ft_strcmp(((struct section*)section)->segname, "__TEXT") == 0))
			print_section_text(section, section, CASTHEADER_X32, flags);
	}
}

void	search_segement__text(char *file, void *map, int is_64, int flags)
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
		parse_segment(header, cmd, ptr, flags);
		ptr += cmd->cmdsize;
		i++;
	}
}
