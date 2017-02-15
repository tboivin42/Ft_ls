//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 17:30:44 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/11 18:17:21 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_recur(t_lst *dir, t_opt *s)
{
	while (dir)
	{
		if (s->o & FLAG_L)
			print_long_2(dir);
		else
		{
			if (strncmp(dir->name, ".", 1) > 0)
				ft_printf("%s\n", dir->name);
			else if (s->o & FLAG_A)
				ft_printf("%s\n", dir->name);
		}
		if (dir)
			dir = dir->next;
	}
}

void	stock_recur(t_lst **dir, t_opt *s)
{
	t_lst	*di;
	char	*tmp;
	DIR 	*rep;

	di = *dir;
	rep = opendir(s->path);
	if (rep == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(di->name);
		return ;
	}
	while ((s->tmp = readdir(rep)) != NULL)
	{
		tmp = ft_strjoin(s->path, s->tmp->d_name);
		stat(tmp, &s->sb) == -1 ? perror(tmp) : 0;
		add_back(&di->inside, s->tmp->d_name, s->sb, s);
	}
	closedir(rep);
	if (s->o & FLAG_T)
		sort(&di->inside, cmp_time);
	else
		sort(&di->inside, cmp_alpha);
	if (s->o & FLAG_LR)
		sort_reverse(&di->inside);
	print_recur(di->inside, s);
	recur(&di->inside, s);
}

void	recur(t_lst **dir, t_opt *s)
{
	t_lst *tmp;

	tmp = *dir;
	if (s->o & FLAG_T)
		sort(&tmp, cmp_time);
	else
		sort(&tmp, cmp_alpha);
	if (s->o & FLAG_LR)
		sort_reverse(&tmp);
	if (s->r == 0)
	{
		print_inside(*dir, s);
		s->r = 1;
	}
	while (tmp)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".") > 0
			&& ft_strcmp(tmp->name, "..") > 0)
			{
				s->path = ft_strjoin(tmp->path, tmp->name);
				s->path = ft_strjoin(s->path, "/");
				ft_printf("\n%s:\n", s->path);
				stock_recur(&tmp, s);
			}
		tmp = tmp->next;
	}
}
