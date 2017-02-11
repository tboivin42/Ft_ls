/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 17:00:18 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/10 17:00:21 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void    order(t_parse *parse, t_opt *s)
{
	sort_ascii(&parse->files);
	sort_ascii(&parse->dir);
	if (s->o & FLAG_LR)
	{
		sort_reverse(&parse->files);
    	sort_reverse(&parse->dir);
  	}
}

char    *get_time(long mtime)
{
    char *tmp;

    tmp = ctime(&mtime);
    tmp = ft_strsub(tmp,4,12);
    return (tmp);
}

void	no_options(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-lratR] [file ...]\n");
	exit(0);
}

void	no_such(char *s)
{
	ft_printf("ft_ls: ");
	perror(s);
}