/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 03:27:29 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/19 16:12:20 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	main_recur2(t_lst *inside, t_opt *s)
{
	while (inside)
	{
		if (s->o & FLAG_L)
			print_long_2(inside, s);
		else if (strncmp(inside->name, ".", 1) > 0)
			ft_printf("%s\n", inside->name);
		inside = inside->next;
	}
}

void	main_recur(t_lst *dir, t_opt *s)
{
	t_lst *tmp;

	while (dir)
	{
		if (dir->next && s->o & FLAG_L)
		{
			count_size(dir, s);
			ft_printf("\n%s:\n", dir->name);
		}
		order(&dir, &dir->inside, s);
		if (dir && dir->inside)
		{
			ft_printf("%s:\n", dir->name);
			tmp = dir->inside;
		}
		main_recur2(dir->inside, s);
		if (dir->next)
			ft_putchar('\n');
		if (dir->inside)
			recur(&tmp, s);
		if (dir->next)
			dir = dir->next;
		else
			return ;
	}
}

void	main_(t_lst *err, t_lst *files, t_lst *dir, t_opt *s)
{
	t_lst *begin_list;

	begin_list = NULL;
	if (dir)
	{
		begin_list = dir;
		ls(&dir, s);
		dir = begin_list;
	}
	order(&dir, &files, s);
	if (s->o & FLAG_LR && dir)
		sort_reverse(&dir->inside);
	if (err || files)
		print_order(err, files, s);
	if (dir && !(s->o & FLAG_UR))
	{
		if (err || files)
			ft_putchar('\n');
		print_inside(dir, s);
	}
	if (s->o & FLAG_UR)
		main_recur(dir, s);
}

int		main(int av, char **ac)
{
	t_opt *s;
	t_lst *dir;
	t_lst *files;
	t_lst *err;

	dir = NULL;
	files = NULL;
	err = NULL;
	s = set_opt(av, ac);
	if (av > 1)
	{
		check_arg(s);
		arg(&err, &files, &dir, s);
	}
	if (err)
		sort(&err, cmp_alpha);
	if (!s->ac[s->k])
	{
		s->i = s->i - 1;
		s->ac[s->i] = ft_strdup(".");
		arg(&err, &files, &dir, s);
	}
	main_(err, files, dir, s);
	return (0);
}
