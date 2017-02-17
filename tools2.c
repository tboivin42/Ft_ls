/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 17:00:18 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:37:10 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		cmp_time(t_lst *l1, t_lst *l2)
{
	if (l1->mtime.tv_sec < l2->mtime.tv_sec)
		return (l1->mtime.tv_sec < l2->mtime.tv_sec);
	else if (l1->mtime.tv_sec == l2->mtime.tv_sec)
	{
		if (l1->mtime.tv_nsec < l2->mtime.tv_nsec)
			return (l1->mtime.tv_nsec < l2->mtime.tv_nsec);
		else if (l1->mtime.tv_nsec == l2->mtime.tv_nsec)
			return (ft_strcmp(l1->name, l2->name));
	}
	return (0);
}

void	order(t_lst *dir, t_lst *files, t_opt *s)
{
	if (s->o & FLAG_T)
	{
		sort(&files, cmp_time);
		sort(&dir, cmp_time);
	}
	else
	{
		sort(&files, cmp_alpha);
		sort(&dir, cmp_alpha);
	}
	if (s->o & FLAG_LR)
	{
		sort_reverse(&files);
		sort_reverse(&dir);
	}
}

char	*get_time(struct timespec mtime)
{
	char *tmp;
	char *tmp1;
	long i;

	tmp = ctime(&mtime.tv_sec);
	tmp1 = tmp;
	i = time(0);
	if (i - 15778458 > mtime.tv_sec || mtime.tv_sec > i)
	{
		tmp = ft_strsub(tmp, 4, 7);
		tmp = ft_strjoin(tmp, " ");
		tmp1 = ft_strsub(tmp1, 20, 4);
		tmp = ft_strjoin(tmp, tmp1);
		return (tmp);
	}
	tmp = ft_strsub(tmp, 4, 12);
	return (tmp);
}

void	no_options(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-1lratR] [file ...]\n");
	exit(0);
}

void	no_such(char *s)
{
	ft_printf("ft_ls: %s: ", s);
	ft_putstr("No such file or directory\n");
}
