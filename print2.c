/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:46:27 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/11 16:47:44 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    print_long(t_parse *parse)
{
  while (parse->files)
  {
    ft_printf("%c", parse->files->dirr);
    ft_printf("%2s", parse->files->rights);
    ft_printf("%4ld ", parse->files->blocks);
    ft_printf("%s  ", parse->files->pw);
    ft_printf("%3s ", parse->files->grp);
    ft_printf("%6ld ",   parse->files->size);
    ft_printf("%s ", parse->files->time);
    ft_printf("%s\n", parse->files->name);
    parse->files = parse->files->next;
  }
  if (parse->dir)
    ft_printf("\n");
}
