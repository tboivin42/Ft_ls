/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:46:27 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 08:10:43 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_inside_(t_lst **dir, t_opt *s)
{
	if ((*dir)->next)
	{
		s->n = 1;
		(*dir) = (*dir)->next;
	}
	else
	{
		(*dir) = (*dir)->next;
		s->n = 0;
	}
}

void	print_dir_inside(t_lst *dir1, t_lst **dir, t_opt *s)
{
	if (ft_strncmp((*dir)->name, ".", 1) > 0)
		ft_printf("%s\n", (*dir)->name);
	else if (s->o & FLAG_A)
		ft_printf("%s\n", (*dir)->name);
	if (!(*dir)->next && dir1->next)
		ft_printf("\n");
	(*dir) = (*dir)->next;
}

void	print_inside(t_lst *dir, t_opt *s)
{
	while (dir)
	{
		sort(&dir->inside, cmp_alpha);
		if (s->o & FLAG_T)
			sort(&dir->inside, cmp_time);
		if (s->o & FLAG_LR)
			sort_reverse(&dir->inside);
		if ((dir->next || s->n == 1) && dir->type == 'd' &&
				ft_strncmp(dir->rights, "-", 1) > 0 && !(s->o & FLAG_UR))
			ft_printf("%s:\n", dir->name);
		if (dir && s->o & FLAG_L)
			print_long_(dir, dir->inside, s);
		else
		{
			while (dir->inside)
				print_dir_inside(dir, &dir->inside, s);
		}
		print_inside_(&dir, s);
	}
}

void	print_long(t_lst *files, t_opt *s)
{
	char	str[257];

	while (files)
	{
		ft_printf("%c", files->type);
		ft_printf("%-11s", files->rights);
		ft_printf("%2ld ", files->blocks);
		ft_printf("%-9s", files->pw);
		ft_printf("%3s ", files->grp);
		if (files->type == 'c' || files->type == 'b')
			ft_printf("%4d, %3d ", files->major, files->minor);
		ft_printf("%6ld ", files->size);
		ft_printf("%s ", files->time);
		if (files->type == 'l')
		{
			ft_printf("%s", files->name);
			s->s = readlink(files->name, str, sizeof(str));
			str[s->s] = '\0';
			ft_printf(" -> %s\n", str);
		}
		else
			ft_printf("%s\n", files->name);
		files = files->next;
	}
}
