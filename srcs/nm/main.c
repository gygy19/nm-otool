/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:52:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/27 19:52:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

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
			if (IS_FLAG_U && !(*flags & flag_u))
				*flags += flag_u;
			if (IS_FLAG_J && !(*flags & flag_j))
				*flags += flag_j;
			if (IS_FLAG_O && !(*flags & flag_o))
				*flags += flag_o;
			if (IS_FLAG_X && !(*flags & flag_x))
				*flags += flag_x;
			o++;
		}
		if (IS_FLAG_VERSION && !(*flags & flag_version))
			*flags += flag_version;
		i++;
	}
	return (*flags > 0);
}

int		inspect_file(char *file, char *prog, int count, int flags)
{
	t_ofile		*ofile;
	struct stat	st;
	int			fd;

	if (count > 1 && !(flags & flag_o))
		ft_printf("\n%s:\n", file);
	if (!file_exists(file))
		return (no_such_file(file, prog));
	if (is_dir(file))
		return (is_directory(file, prog));
	if (!is_regular(file))
		return (not_object_file(file, prog));
	if ((fd = open(file, O_RDONLY)) < 3)
		return (permission_denied(file, prog));
	fstat(fd, &st);
	if (!(ofile = process_ofile(file, fd, st, prog)))
		return (0);
	if (ofile->is_64 == false && ofile->is_32 == false)
		return (not_object_file(file, prog));
	ofile->flags = flags;
	ofile->name = file;
	ofile->prog = prog;
	select_function_by_os(ofile, ft_nm64, ft_nm32);
	free_ofile(ofile);
	return (0);
}

int		getcountfiles(int argc, char **argv)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			count++;
		}
		i++;
	}
	return (count);
}

int		main(int argc, char **argv)
{
	int			flags;
	int			i;
	int			count;

	i = 1;
	count = 0;
	if (!check_flags(argc, argv, &flags) && argc == 1)
		return (inspect_file("a.out", argv[0], count, flags));
	if (flags & flag_version)
	{
		print_version(argv[0]);
		return (0);
	}
	count = getcountfiles(argc, argv);
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			inspect_file(argv[i], argv[0], count, flags);
		}
		i++;
	}
	if (count == 0)
		return (print_flags(argv[0]));
	return (0);
}
