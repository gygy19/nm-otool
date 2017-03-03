/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 10:48:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	print_addr(int val)
{
	char	*tmp;
	size_t	i;

	i = ADDR_LEN;
	tmp = ft_uitoabase(val, ADDR_BASE);
	if (tmp != NULL && ft_strlen(tmp) > 0)
	{
		ft_putstr(FIRSTADDR);
		while (i > ft_strlen(tmp))
		{
			ft_putchar('0');
			i--;
		}
		ft_putstr(tmp);
		free(tmp);
	}
	else
	{
		ft_putstr(FIRSTADDR);
		ft_putstr("00000000");
	}
}
