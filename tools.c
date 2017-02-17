/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 07:17:14 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:36:09 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

// unsigned long	get_blocks(struct)

t_lst	*get_arg(char *av, struct stat sb, t_opt *s)
{
	t_lst			*tmp;
	struct passwd	*pwd;
	struct group	*grp;

	if (!(tmp = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	if ((pwd = getpwuid(sb.st_uid)) != NULL)
		tmp->pw = pwd->pw_name;
	if ((grp = getgrgid(sb.st_gid)) != NULL)
		tmp->grp = grp->gr_name;
	tmp->blocks2 = sb.st_blocks;
	// ft_printf("%ld\n", tmp->blocks2);
	tmp->mtime = sb.st_mtimespec;
	tmp->path = s->path;
	tmp->time = get_time(tmp->mtime);
	tmp->name = ft_strdup(av);
	tmp->next = NULL;
	tmp->size = sb.st_size;
	tmp->blocks = sb.st_nlink;
	tmp->rights = get_rights(sb);
	tmp->type = get_type(sb);
	tmp->inside = NULL;
	return (tmp);
}

void	add_back(t_lst **new, char *ac, struct stat sb, t_opt *s)
{
	t_lst *tmp;

	tmp = *new;
	if (!tmp)
	{
		*new = get_arg(ac, sb, s);
		if (s->o & FLAG_T)
			sort(&tmp, cmp_time);
		else
			sort(&tmp, cmp_alpha);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = get_arg(ac, sb, s);
	if (s->o & FLAG_T)
		sort(&tmp, cmp_time);
	else
		sort(&tmp, cmp_alpha);
}

void	sort_reverse(t_lst **list)
{
	t_lst	*tmp;
	t_lst	*tmp2;
	t_lst	*tmp3;

	tmp = *list;
	tmp2 = NULL;
	while (tmp)
	{
		tmp3 = tmp2;
		tmp2 = tmp;
		tmp = tmp->next;
		tmp2->next = tmp3;
	}
	*list = tmp2;
}
