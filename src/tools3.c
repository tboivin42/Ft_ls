/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 07:37:32 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:37:33 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	count_size(t_lst *dir, t_opt *s)
{
	t_lst	*tmp;
	size_t	blocks;

	if (dir->inside)
		tmp = dir->inside;
	else
		tmp = dir;
	blocks = 0;
	while (tmp)
	{
		if ((s->o & FLAG_A))
			blocks += tmp->blocks2;
		else if (ft_strncmp(tmp->name, ".", 1) != 0)
			blocks += tmp->blocks2;
		tmp = tmp->next;
	}
	if (dir->inside)
		ft_printf("%s:\n", dir->name);
	if (dir->next)
		ft_printf("total %d\n", blocks);
}

void	elem_cpy(t_lst **src, t_lst *cpy)
{
	(*src)->name = cpy->name;
	(*src)->path = cpy->path;
	(*src)->size = cpy->size;
	(*src)->pw = cpy->pw;
	(*src)->grp = cpy->grp;
	(*src)->time = cpy->time;
	(*src)->blocks = cpy->blocks;
	(*src)->mtime = cpy->mtime;
	(*src)->type = cpy->type;
	(*src)->rights = cpy->rights;
}

void	swap_elem(t_lst **a, t_lst **b)
{
	t_lst tmp;

	tmp = **a;
	elem_cpy(a, *b);
	elem_cpy(b, &tmp);
}

int		cmp_alpha(t_lst *elem1, t_lst *elem2)
{
	return (ft_strcmp(elem1->name, elem2->name));
}

void	sort(t_lst **list, int (*cmp)(t_lst *elem1, t_lst *elem2))
{
	t_lst *a;
	t_lst *b;

	a = *list;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (cmp(a, b) > 0)
				swap_elem(&a, &b);
			b = b->next;
		}
		a = a->next;
	}
}
