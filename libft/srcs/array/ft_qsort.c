/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:46:50 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/04 17:46:52 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include "mapft.h"
#include "libft.h"

static void	cmpqsortstring(char **base, int *tmp, size_t size,\
			int (*compar)(const void*, const void*))
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (base[i] != NULL && base[i][0] != '\0' && *tmp != -1\
			&& compar(base[i], base[*tmp]) < 0)
			*tmp = i;
		else if (base[i] != NULL && *tmp == -1 && base[i][0] != '\0')
			*tmp = i;
		i++;
	}
}

static void	asigncurrenttabtobase(char **base, char **tab,\
			char *c1, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		base[i] = NULL;
		if (c1[i] != '\0')
		{
			base[i] = tab[i];
			base[i][0] = c1[i];
		}
		i++;
	}
	free(c1);
	free(tab);
}

static void	ft_qsort_string(char **base, size_t mmemb,\
			int (*compar)(const void *, const void *), char **tab)
{
	int		tmp;
	size_t	count;
	char	*c1;

	if (tab == NULL)
		return ;
	if (!(c1 = ft_strnew(mmemb)))
		return ;
	count = 0;
	while (1)
	{
		tmp = -1;
		cmpqsortstring(base, &tmp, mmemb, compar);
		if (tmp == -1)
			break ;
		tab[count] = base[tmp];
		c1[count++] = base[tmp][0];
		base[tmp][0] = '\0';
	}
	asigncurrenttabtobase(base, tab, c1, mmemb);
}

static void	ft_qsort_integer(int *base, size_t mmemb,\
			int (*compar)(const void *, const void *))
{
	(void)compar;
	(void)mmemb;
	(void)base;
}

void		ft_qsort(void *base, size_t mmemb, char *type,\
			int (*compar)(const void *, const void *))
{
	void	*tmp;

	tmp = malloc(sizeof(char*) * mmemb);
	if (strcmp(type, "int*") == 0)
		ft_qsort_integer(base, mmemb, compar);
	else if (strcmp(type, "char*") == 0)
		ft_qsort_string(base, mmemb, compar, tmp);
}
