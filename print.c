/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:28:34 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/26 19:23:01 by tboivin          ###   ########.fr       */
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
    sort_reverse(&parse->dir);  }
}

void    print_long(t_parse *parse)
{
  while (parse->files)
  {
    ft_printf("%c", parse->files->dirr);
    ft_printf("%s ", parse->files->rights);
    ft_printf("%2ld ", parse->files->blocks);
    ft_printf("%s  ", parse->files->pw);
    ft_printf(" %s ", parse->files->grp);
    ft_printf("%5ld ", parse->files->size);
    ft_printf("%s ", parse->files->time);
    ft_printf("%s\n", parse->files->name);
    parse->files = parse->files->next;
  }
}

void    print_long_(t_lst *dir, t_opt *s)
{
    while (dir)
    {
      if (s->o & FLAG_A)
      {
        ft_printf("%c", dir->dirr);
        ft_printf("%2s", dir->rights);
        ft_printf("%3ld ", dir->blocks);
        ft_printf("%s  ", dir->pw);
        ft_printf(" %s ",dir->grp);
        ft_printf("%5ld ", dir->size);
        ft_printf("%s ", dir->time);
        ft_printf("%s\n", dir->name);
      }
      dir = dir->next;
    }
}

void    print_inside(t_parse *parse, t_opt *s)
{
    while (parse->dir)
    {
      sort_ascii(&parse->dir->inside);
      if (s->o & FLAG_LR)
        sort_reverse(&parse->dir->inside);
      ft_printf("%s:\n", parse->dir->name);
      if (s->o & FLAG_L)
        print_long_(parse->dir->inside, s);
      else
      {
        while (parse->dir->inside)
        {
          if (ft_strncmp(parse->dir->inside->name, ".", 1) > 0)
            ft_printf("%s\n", parse->dir->inside->name);
          else if (s->o & FLAG_A)
            ft_printf("%s\n", parse->dir->inside->name);
          parse->dir->inside = parse->dir->inside->next;
        }
      }
      ft_printf("\n");
      parse->dir = parse->dir->next;
    }
}

void    print_order(t_parse *parse, t_opt *s)
{
  order(parse, s);
  while (parse->err)
  {
  	no_such(parse->err->name);
  	parse->err = parse->err->next;
  }
  if (s->o & FLAG_L && parse->files)
    return(print_long(parse));
  while (parse->files)
  {
  	ft_printf("%s\n", parse->files->name);
    parse->files = parse->files->next;
  }
  if (parse->dir)
    print_inside(parse, s);
}
