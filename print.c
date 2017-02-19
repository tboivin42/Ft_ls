/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:28:34 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/19 16:14:00 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	print_long_l(t_lst **dir)
{
	char	str[257];
	int		i;

	i = 0;
	ft_printf("%s", (*dir)->name);
	i = readlink(ft_strjoin((*dir)->path, (*dir)->name),
			str, sizeof(str));
	str[i] = '\0';
	ft_printf(" -> %s\n", str);
}

void	print_long_3(t_lst *dir)
{
	ft_printf("%c", dir->type);
	ft_printf("%-11s", dir->rights);
	ft_printf("%2ld ", dir->blocks);
	ft_printf("%-9s", dir->pw);
	ft_printf("%3s ", dir->grp);
	ft_printf("%6ld ", dir->size);
	ft_printf("%s ", dir->time);
	if (dir->type == 'l')
		print_long_l(&dir);
	else
		ft_printf("%s\n", dir->name);
}

void	print_long_2(t_lst *dir, t_opt *s)
{
	if (s->o & FLAG_UR && s->o & FLAG_A)
		print_long_3(dir);
	else if (strncmp(dir->name, ".", 1) > 0)
	{
		ft_printf("%c", dir->type);
		ft_printf("%-11s", dir->rights);
		ft_printf("%2ld ", dir->blocks);
		ft_printf("%-9s", dir->pw);
		ft_printf("%3s ", dir->grp);
		if (dir->type == 'c' || dir->type == 'b')
			ft_printf("%4d, %3d ", dir->major, dir->minor);
		else
			ft_printf("%6ld ", dir->size);
		ft_printf("%s ", dir->time);
		if (dir->type == 'l')
			print_long_l(&dir);
		else
			ft_printf("%s\n", dir->name);
	}
}

void	print_long_(t_lst *tmp, t_lst *dir, t_opt *s)
{
	if (s->o & FLAG_L)
		count_size(dir, s);
	while (dir)
	{
		if (s->o & FLAG_A)
		{
			ft_printf("%c", dir->type);
			ft_printf("%-11s", dir->rights);
			ft_printf("%3ld ", dir->blocks);
			ft_printf("%-9s", dir->pw);
			ft_printf("%3s ", dir->grp);
			ft_printf("%6ld ", dir->size);
			ft_printf("%s ", dir->time);
			if (dir->type == 'l')
				print_long_l(&dir);
			else
				ft_printf("%s\n", dir->name);
		}
		else
			print_long_2(dir, s);
		if (tmp->next && !dir->next)
			ft_printf("\n");
		dir = dir->next;
	}
}

void	print_order(t_lst *err, t_lst *files, t_opt *s)
{
	while (err)
	{
		s->n = 1;
		no_such(err->name);
		err = err->next;
	}
	if (s->o & FLAG_L && files)
	{
		s->n = 1;
		print_long(files, s);
	}
	while (files && !(s->o & FLAG_L))
	{
		s->n = 1;
		ft_printf("%s\n", files->name);
		files = files->next;
	}
}
