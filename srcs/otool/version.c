/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_version.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:19:21 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:19:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	*cpu_type_name(cpu_type_t cpu_type)
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
