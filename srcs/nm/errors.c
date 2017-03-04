/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:12:47 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 16:12:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		isdirectory(char *file, char *prog)
{
	ft_printf("%s: '%s': Is a directory.\n", prog, file);
	return (0);
}

int		nosuchfile(char *file, char *prog)
{
	ft_printf("%s: '%s': No such file or directory.\n", prog, file);
	return (0);
}

int		permissiondenied(char *file, char *prog)
{
	ft_printf("%s: '%s': Permission denied.\n", prog, file);
	return (0);
}

int		notobjectfile(char *file, char *prog)
{
	ft_printf("%s: '%s': The file was", prog, file);
	ft_printf(" not recognized as a valid object file.\n");
	return (0);
}

int		printflags(char *prog)
{
	ft_printf("Usage: %s [-ht] [--version] <object file> ...\n", prog);
	ft_printf("\t-h print the mach header\n");
	ft_printf("\t-t print the text section\n");
	return (0);
}
