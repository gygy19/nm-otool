/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:39:27 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/01 19:39:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	print_hexa(int val)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_uitoabase(val, "0123456789abcdef");
	if (tmp != NULL && ft_strlen(tmp) > 0)
	{
		ft_putchar(tmp[ft_strlen(tmp) - 1]);
		free(tmp);
	}
	else
		ft_putstr("0");
}
