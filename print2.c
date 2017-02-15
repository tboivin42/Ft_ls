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

void    print_long(t_lst *files)
{
  while (files)
  {
    ft_printf("%c", files->type);
    ft_printf("%2s", files->rights);
    ft_printf("%4ld ", files->blocks);
    ft_printf("%s  ", files->pw);
    ft_printf("%3s ", files->grp);
    ft_printf("%6ld ",   files->size);
    ft_printf("%s ", files->time);
    ft_printf("%s\n", files->name);
    files = files->next;
  }
  // if (parse->dir)
  //   ft_printf("\n");
}
