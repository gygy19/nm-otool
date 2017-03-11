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
	ft_printf("%s: '%s': Is a directory.\n", prog, file);
	return (0);
}

int		no_such_file(char *file, char *prog)
{
	ft_printf("%s: '%s': No such file or directory.\n", prog, file);
	return (0);
}

int		permission_denied(char *file, char *prog)
{
	ft_printf("%s: '%s': Permission denied.\n", prog, file);
	return (0);
}

int		not_object_file(char *file, char *prog)
{
	ft_printf("%s: '%s': The file was", prog, file);
	ft_printf(" not recognized as a valid object file.\n");
	return (0);
}

int		print_flags(char *prog)
{
	ft_printf("Usage: %s [-ujox] [--version] <object file> ...\n", prog);
	ft_printf("\t-u Print ulterior used functions\n");
	ft_printf("\t-j Print simple symbol\n");
	ft_printf("\t-o Print symbol entry and name file\n");
	ft_printf("\t-x Print symbol entry in hex, Mach-O only\n");
	return (0);
}
