/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:38:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 17:38:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		isdir(const char *file)
{
	struct stat buf;

	if (!fileexists(file))
		return (0);
	stat(file, &buf);
	return (S_ISDIR(buf.st_mode));
}
