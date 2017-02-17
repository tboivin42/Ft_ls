/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 17:30:44 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:33:33 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_recu(t_lst **dir, t_opt *s)
{
	if (s->o & FLAG_T)
		sort(&(*dir), cmp_time);
	else
		sort(&(*dir), cmp_alpha);
	if (s->o & FLAG_LR)
		sort_reverse(&(*dir));
}

void	print_recur(t_lst *dir, t_opt *s)
{
	if (s->o & FLAG_L && dir)
    	ft_printf("Total %ld\n", dir->blocks2);
	while (dir)
	{
		if (s->o & FLAG_L)
			print_long_2(dir, s);
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
	t_lst	*directory;
	char	*tmp;
	DIR		*rep;

	di = *dir;
	directory = NULL;
	rep = opendir(s->path);
	if (rep == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(di->name);
		di = di->next;
		return ;
	}
	while ((s->tmp = readdir(rep)) != NULL)
	{
		tmp = ft_strjoin(s->path, s->tmp->d_name);
		lstat(tmp, &s->sb) == -1 ? perror(tmp) : 0;
		add_back(&directory, s->tmp->d_name, s->sb, s);
	}
	closedir(rep);
	sort_recu(&directory, s);
	print_recur(directory, s);
	recur(&directory, s);
}

void	recur(t_lst **dir, t_opt *s)
{
	t_lst *tmp;

	tmp = *dir;
	while (tmp)
	{
		if (!(s->o & FLAG_A) && tmp->type == 'd' && 
			ft_strncmp(tmp->name, ".", 1) == 0)
		{
			tmp->path = s->path;
			// if (tmp)
				// tmp = tmp->next;
		}
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".") != 0
			&& ft_strcmp(tmp->name, "..") != 0)
		{
			s->path = ft_strjoin(tmp->path, tmp->name);
			s->path = ft_strjoin(s->path, "/");
			ft_printf("\n%s:\n", s->path);
			stock_recur(&tmp, s);
		}
		tmp = tmp->next;
	}
}
