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

int		getflags(int st)
{
	static int	flags = 0;

	if (st != 0)
		flags = st;
	return (flags);
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
			if (IS_FLAG_U && !(*flags & flag_u))
				*flags += flag_u;
			if (IS_FLAG_J && !(*flags & flag_j))
				*flags += flag_j;
			o++;
		}
		if (IS_FLAG_VERSION && !(*flags & flag_version))
			*flags += flag_version;
		i++;
	}
	getflags(*flags);
	return (*flags > 0);
}

int		inspect_file(char *file, char *prog, int count)
{
	void		*map;
	struct stat	st;
	int			fd;

	if (count > 1)
		ft_printf("\n%s:\n", file);
	if (!fileexists(file))
		return (nosuchfile(file, prog));
	if (isdir(file))
		return (isdirectory(file, prog));
	if (!is_regular(file))
		return (notobjectfile(file, prog));
	if ((fd = open(file, O_RDONLY)) < 3)
		return (permissiondenied(file, prog));
	fstat(fd, &st);
	if ((map = ft_mmap(fd, st.st_size)) == MAP_FAILED)
		return (permissiondenied(file, prog));
	if (((struct mach_header_64*)map)->filetype != 2
		&& ((struct mach_header_64*)map)->filetype != 1
		&& ((struct mach_header_64*)map)->filetype != UNIVERSAL_BINARY_TYPE)
		return (notobjectfile(file, prog));
	search_syms(file, map, is_magic_64(get_magic(map)));
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
		return (inspect_file("a.out", argv[0], count));
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
			inspect_file(argv[i], argv[0], count);
		}
		i++;
	}
	if (count == 0)
		return (printflags(argv[0]));
	return (0);
}
