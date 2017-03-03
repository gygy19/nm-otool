/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:51:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/27 19:51:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <stdio.h>

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

char *cpu_type_name(cpu_type_t cpu_type)
{
	if (CPU_TYPE_I386 == cpu_type)
		return ("i386");
	if (CPU_TYPE_X86_64 == cpu_type)
		return ("x86_64");
	if (CPU_TYPE_ARM == cpu_type)
		return ("arm");
	if (CPU_TYPE_ARM64 == cpu_type)
		return ("arm64");
	return ("unknown");
}

void	printheader_infos(void *map)
{
	struct mach_header	*header;

	header = map;
	ft_printf("Mach header\n");
	ft_printf(" %10s cputype cpusubtype  caps    ", "magic");
	ft_printf("filetype ncmds sizeofcmds      flags\n");
	printf(" %#10x %8d %10d %#10x  %5d %5d %10d %0#.8x\n",\
		header->magic, header->cputype, 3, header->cpusubtype & CPU_SUBTYPE_MASK,\
		header->filetype, header->ncmds, header->sizeofcmds, header->flags);
}

void	print_version(void *map)
{
	struct mach_header	*header;

	header = map;
	ft_printf("llvm-otool(1): Jguyet Student42. version 1\n");
	ft_printf("Version 1.0.0 (clang-800.0.42.1)\n");
	ft_printf("  Optimized build.\n");
	ft_printf("  Default target: %s\n", cpu_type_name(header->cputype));
	ft_printf("  Host CPU: ??\n\n");
	ft_printf("  Registered Targets:\n");
	ft_printf("  %10s - %s\n", "arm", "ARM");
	ft_printf("  %10s - %s\n", "arm64", "ARM64");
	ft_printf("  %10s - %s\n", "i386", "I386");
	ft_printf("  %10s - %s\n", "x86-64", "64-bit X86: EM64T and AMD64");
}

int		check_flags(int argc, char **argv, int *flags)
{
	int i;
	int o;

	*flags = 0;
	i = 1;
	while (i < argc)
	{
		o = 0;
		while (argv[i][o] != '\0')
		{
			if (argv[i][0] != '-')
				break ;
			if (IS_FLAG_H && !(*flags & flag_h))
				*flags += flag_h;
			if (IS_FLAG_T && !(*flags & flag_t))
				*flags += flag_t;
			o++;
		}
		if (IS_FLAG_VERSION && !(*flags & flag_version))
				*flags += flag_version;
		i++;
	}
	return (*flags > 0);
}

int		inspect_file(char *file, int flags)
{
	void		*map;
	struct stat	st;
	int			fd;

	if ((fd = open(file, O_RDWR)) < 3)
		return (1);
	if (fstat(fd, &st) == -1)
		return (1);
	if ((map = ft_mmap(fd, st.st_size)) == MAP_FAILED)
		return (1);
	if (flags & flag_t)
		search_segement__text(file, map, is_magic_64(get_magic(map)));
	if (flags & flag_h)
		printheader_infos(map);
	return (0);
}

int		main(int argc, char **argv)
{
	int			flags;
	int			i;

	i = 1;
	if (!check_flags(argc, argv, &flags))
	{
		ft_printf("Usage: %s [-ht] [--version] <object file> ...\n", argv[0]);
		ft_printf("\t-h print the mach header\n");
		ft_printf("\t-t print the text section\n");
		return (0);
	}
	if (flags & flag_version)
	{
		print_version(argv[0]);
		return (0);
	}
	if (i < argc && argv[i][0] == '-')
		i++;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			inspect_file(argv[i], flags);
		i++;
	}
	return (0);
}
