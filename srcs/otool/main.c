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

int		inspect_file(char *file, int flags, char *prog)
{
	void		*map;
	struct stat	st;
	int			fd;

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
	if (((struct mach_header_64*)map)->filetype > 3
		|| ((struct mach_header_64*)map)->filetype < 1)
		return (notobjectfile(file, prog));
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
	int			count;

	i = 1;
	count = 0;
	if (!check_flags(argc, argv, &flags))
		return (printflags(argv[0]));
	if (flags & flag_version)
	{
		print_version(argv[0]);
		return (0);
	}
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			inspect_file(argv[i], flags, argv[0]);
			count++;
		}
		i++;
	}
	if (count == 0)
		return (printflags(argv[0]));
	return (0);
}
