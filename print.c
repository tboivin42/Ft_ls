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
  char str[257];
  int i;

  i = 0;
  if (strncmp(dir->name, ".", 1) > 0)
  {
    ft_printf("%c", dir->type);
    ft_printf("%2s", dir->rights);
    ft_printf("%4ld ", dir->blocks);
    ft_printf("%s  ", dir->pw);
    ft_printf("%3s ",dir->grp);
    ft_printf("%6ld ", dir->size);
    ft_printf("%s ", dir->time);
    if(dir->type == 'l')
    {
      ft_printf("%s", dir->name);
      i = readlink(ft_strjoin(dir->path, dir->name), str, sizeof(str));
      str[i] = '\0';
      ft_printf(" -> %s\n", str);
    }
    else
      ft_printf("%s\n", dir->name);
  }
}

void    print_long_(t_lst *dir, t_opt *s)
{
    while (dir)
    {
      if (s->o & FLAG_A)
      {
        ft_printf("%c", dir->type);
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
      if (!dir->next)
            ft_printf("\n");
      dir = dir->next;
    }
}

void    print_inside_(t_lst **dir, t_opt *s)
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

void    print_inside(t_lst *dir, t_opt *s)
{
    while (dir)
    {
      sort(&dir->inside, cmp_alpha);
      if (s->o & FLAG_T)
        sort(&dir->inside, cmp_time);
      if (s->o & FLAG_LR)
        sort_reverse(&dir->inside);
      if ((dir->next || s->n == 1) && dir->type == 'd')
        ft_printf("%s:\n", dir->name);
      if (s->o & FLAG_L)
        print_long_(dir->inside, s);
      else
      {
        while (dir->inside)
        {
          if (ft_strncmp(dir->inside->name, ".", 1) > 0)
            ft_printf("%s\n", dir->inside->name);
          else if (s->o & FLAG_A)
            ft_printf("%s\n", dir->inside->name);
          if (!dir->inside->next && dir->next)
            ft_printf("\n");
          dir->inside = dir->inside->next;
        }
      }
      print_inside_(&dir, s);
    }
}

void    print_order(t_lst *err, t_lst *files, t_opt *s)
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
    print_long(files);
  }
  while (files)
  {
    s->n = 1;
  	ft_printf("%s\n", files->name);
    files = files->next;
    // if (parse->dir && !parse->files)
    //   ft_printf("\n");
  }
}
