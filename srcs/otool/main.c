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

static void	check_flags_two(int *flags, char **argv, int i, int o)
{
	if (IS_FLAG_H && !(*flags & flag_h))
		*flags += flag_h;
	if (IS_FLAG_T && !(*flags & flag_t))
		*flags += flag_t;
	if (IS_FLAG_A && !(*flags & flag_a))
		*flags += flag_a;
	if (IS_FLAG_V && !(*flags & flag_v))
		*flags += flag_v;
}

int			check_flags(int argc, char **argv, int *flags)
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
			check_flags_two(flags, argv, i, o);
			o++;
		}
		if (IS_FLAG_VERSION && !(*flags & flag_version))
			*flags += flag_version;
		i++;
	}
	return (*flags > 0);
}

int			check_errors(char *file, char *prog, int *i, int *fd)
{
	if (!file_exists(file))
	{
		*i = ERROR_ARGC;
		return (no_such_file(file, prog));
	}
	if (is_dir(file))
	{
		*i = ERROR_ARGC;
		return (is_directory(file, prog));
	}
	if (!is_regular(file))
	{
		*i = ERROR_ARGC;
		return (not_object_file(file, prog));
	}
	if ((*fd = open(file, O_RDONLY)) < 3)
	{
		*i = ERROR_ARGC;
		return (permission_denied(file, prog));
	}
	return (0);
}

int			inspect_file(char *file, int flags, char *prog, int *i)
{
	t_ofile		*ofile;
	struct stat	st;
	int			fd;

	ft_printf("%s:\n", file);
	if (check_errors(file, prog, i, &fd) == true)
		return (0);
	fstat(fd, &st);
	if (!(ofile = process_ofile(file, fd, st, prog)))
		return (0);
	if (ofile->is_64 == false && ofile->is_32 == false)
	{
		*i = ERROR_ARGC;
		return (not_object_file(file, prog));
	}
	ofile->flags = flags;
	if (ofile->flags & flag_h)
		select_function_by_os(ofile, print_header_64, print_header_32);
	if ((ofile->flags & flag_t) && !(ofile->flags & flag_v))
		select_function_by_os(ofile, ft_otool64, ft_otool32);
	if ((ofile->flags & flag_t) && (ofile->flags & flag_v))
		select_function_by_os(ofile, ftv_otool64, ftv_otool32);
	free_ofile(ofile);
	return (0);
}

int			main(int argc, char **argv)
{
	int			flags;
	int			i;
	int			count;

	i = 1;
	count = 0;
	if (!check_flags(argc, argv, &flags))
		return (print_flags(argv[0]));
	if (flags & flag_version)
	{
		print_version(argv[0]);
		return (0);
	}
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			inspect_file(argv[i], flags, argv[0], &i);
			count++;
		}
		i++;
	}
	if (count == 0)
		return (print_flags(argv[0]));
	return (0);
}
