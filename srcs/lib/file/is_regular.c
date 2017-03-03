/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_regular.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:35:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:35:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		is_regular(const char *file)
{
	struct stat buf;

	if (!fileexists(file))
		return (0);
	stat(file, &buf);
	return (S_ISREG(buf.st_mode));
}
