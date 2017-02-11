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

void    print_long_2(t_lst *dir)
{
  if (strncmp(dir->name, ".", 1) > 0)
  {
    ft_printf("%c", dir->dirr);
    ft_printf("%2s", dir->rights);
    ft_printf("%4ld ", dir->blocks);
    ft_printf("%s  ", dir->pw);
    ft_printf("%3s ",dir->grp);
    ft_printf("%6ld ", dir->size);
    ft_printf("%s ", dir->time);
    ft_printf("%s\n", dir->name);
  }
}

void    print_long_(t_parse *parse, t_lst *dir, t_opt *s)
{
    while (dir)
    {
      if (s->o & FLAG_A)
      {
        ft_printf("%c", dir->dirr);
        ft_printf("%2s", dir->rights);
        ft_printf("%4ld ", dir->blocks);
        ft_printf("%s  ", dir->pw);
        ft_printf("%3s ",dir->grp);
        ft_printf("%6ld ", dir->size);
        ft_printf("%s ", dir->time);
        ft_printf("%s\n", dir->name);
      }
      else
        print_long_2(dir);
      if (!dir->next && parse->dir->next)
            ft_printf("\n");
      dir = dir->next;
    }
}

void    print_inside_(t_parse *parse, t_opt *s)
{
    if (parse->dir->next)
    {
      s->n = 1;
      parse->dir = parse->dir->next;
    }
    else
    {
      parse->dir = parse->dir->next;
      s->n = 0; 
    }
}

void    print_inside(t_parse *parse, t_opt *s)
{
    while (parse->dir)
    {
      sort_ascii(&parse->dir->inside);
      if (s->o & FLAG_LR)
        sort_reverse(&parse->dir->inside);
      if (parse->dir->next || s->n ==1)
        ft_printf("%s:\n", parse->dir->name);
      if (s->o & FLAG_L)
        print_long_(parse, parse->dir->inside, s);
      else
      {
        while (parse->dir->inside)
        {
          if (ft_strncmp(parse->dir->inside->name, ".", 1) > 0)
            ft_printf("%s\n", parse->dir->inside->name);
          else if (s->o & FLAG_A)
            ft_printf("%s\n", parse->dir->inside->name);
          if (!parse->dir->inside->next && parse->dir->next)
            ft_printf("\n");
          parse->dir->inside = parse->dir->inside->next;
        }
      }
      print_inside_(parse, s);
    }
}

void    print_order(t_parse *parse, t_opt *s)
{
  order(parse, s);
  while (parse->err)
  {
    s->n = 1;
  	no_such(parse->err->name);
  	parse->err = parse->err->next;
  }
  if (s->o & FLAG_L && parse->files)
  {
    s->n = 1;
    print_long(parse);
  }
  while (parse->files)
  {
    s->n = 1;
  	ft_printf("%s\n", parse->files->name);
    parse->files = parse->files->next;
    if (parse->dir && !parse->files)
      ft_printf("\n");
  }
  if (parse->dir)
    print_inside(parse, s);
}
