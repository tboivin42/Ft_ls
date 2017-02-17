/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 03:27:29 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:28:27 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	main_(t_lst *err, t_lst *files, t_lst *dir, t_opt *s)
{
	t_lst *begin_list;
	t_lst *tmp;
	t_lst *tmp2;

	tmp = NULL;
	tmp2 = dir;
	begin_list = NULL;
	if (dir)
	{
		begin_list = dir;
		ls(&dir, s);
		dir = begin_list;
	}
	order(dir, files, s);
	if (s->o & FLAG_LR)
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
	while (dir)
	{
		if (dir->next)
			ft_printf("\n%s:\n", dir->name);
		if ((s->o & FLAG_UR) && dir)
		{
			tmp = dir->inside;
			if (s->o & FLAG_T)
				sort(&tmp, cmp_time);
			else
				sort(&tmp, cmp_alpha);
			if (s->o & FLAG_LR)
				sort_reverse(&tmp);
			// print_inside(dir, s);
			// tmp = dir->inside;
			while (dir->inside)
			{
				if (s->o & FLAG_T)
					sort(&dir->inside, cmp_time);
				else
					sort(&dir->inside, cmp_alpha);
				if (s->o & FLAG_LR)
					sort_reverse(&dir->inside);
				// ft_printf("%s:", dir->name);
				if (strncmp(dir->inside->name, ".", 1) > 0)
					ft_printf("%s\n", dir->inside->name);
				dir->inside = dir->inside->next;
			}
			recur(&tmp, s);
		}
		if (dir->next)
			dir = dir->next;
		else
			return ;
	}
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
		s->k -= 1;
		s->i = s->i - 1;
		s->ac[s->i] = ft_strdup(".");
		arg(&err, &files, &dir, s);
	}
	main_(err, files, dir, s);
	return (0);
}
