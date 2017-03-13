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

int		is_directory(char *file, char *prog)
{
	ft_fprintf(2, "%s: '%s': Is a directory.\n", prog, file);
	return (1);
}

int		no_such_file(char *file, char *prog)
{
	ft_fprintf(2, "%s: '%s': No such file or directory.\n", prog, file);
	return (1);
}

int		permission_denied(char *file, char *prog)
{
	ft_fprintf(2, "%s: '%s': Permission denied.\n", prog, file);
	return (1);
}

int		not_object_file(char *file, char *prog)
{
	ft_fprintf(2, "%s: '%s': The file was", prog, file);
	ft_fprintf(2, " not recognized as a valid object file.\n");
	return (1);
}

int		print_flags(char *prog)
{
	ft_printf("Usage: %s [-ht] [--version] <object file> ...\n", prog);
	ft_printf("\t-h print the mach header\n");
	ft_printf("\t-t print the text section\n");
	return (0);
}
