/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 22:12:07 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/28 22:12:09 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	ls(t_lst **dir, t_opt *s)
{
	t_lst	*di;
	char	*tmp;
	DIR *rep;

	rep = NULL;
	di = *dir;
	while (di)
	{
		s->path = ft_strjoin(di->name, "/");
		rep = opendir(s->path);
		while (rep == NULL)
		{
			if (!di->next)
				return ;
			di = di->next;
			s->path = ft_strjoin(di->name, "/");
			rep = opendir(s->path);
		}
		while ((s->tmp = readdir(rep)) != NULL)
		{
			tmp = ft_strjoin(s->path, s->tmp->d_name);
			lstat(tmp, &s->sb) == -1 ? perror(tmp) : 0;
			add_back(&di->inside, s->tmp->d_name, s->sb, s);
		}
		di = di->next;
	}
}
