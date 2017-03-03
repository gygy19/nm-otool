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

int		fileexists(const char *file)
{
	struct stat buf;

	return (stat(file, &buf) == 0);
}

void	inspect_file(char *file, int flags)
{
	void		*map;
	struct stat	st;
	int			fd;

	if (!fileexists(file))
		return ;
	if ((fd = open(file, O_RDWR)) < 3)
		return ;
	fstat(fd, &st);
	if ((map = ft_mmap(fd, st.st_size)) == MAP_FAILED)
		return ;
	if (flags & flag_t)
		search_segement__text(file, map, is_magic_64(get_magic(map)));
	if (flags & flag_h)
		printheader_infos(map);
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
	while (i < argc)
	{
		if (argv[i][0] != '-')
			inspect_file(argv[i], flags);
		i++;
	}
	return (0);
}
