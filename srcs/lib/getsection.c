/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:29:33 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/04 16:29:35 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static struct section_64	*get_section_64(void *header,\
							struct load_command *cmd, void *ptr)
{
	int							is_64;
	struct section_64			*section;

	section = NULL;
	is_64 = is_magic_64(get_magic(header));
	if (IS_SEGMENT_X64 && IS_X64)
	{
		section = ptr + SIZE_SEG;
	}
	else if (IS_SEGMENT_X32 && IS_X32)
	{
		section = ptr + SIZE_SEG;
	}
	return (section);
}

struct section_64			*getsection(void *map, uint32_t id, int is_64)
{
	void						*header;
	uint32_t					i;
	struct load_command			*cmd;
	void						*ptr;

	header = map;
	i = 0;
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
		if (i == id)
			return (get_section_64(header, cmd, ptr));
		ptr += cmd->cmdsize;
		i++;
	}
	return (NULL);
}
