/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 07:17:14 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/26 19:35:02 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_lst   *get_arg(char *av, struct stat sb)
{
   t_lst   *tmp;
   struct passwd *pwd;
   struct group *grp;

    if (!(tmp = (t_lst*)malloc(sizeof(t_lst))))
        return (NULL);
    if ((pwd = getpwuid(sb.st_uid)) != NULL)
        tmp->pw = pwd->pw_name;
    if ((grp = getgrgid(sb.st_gid)) != NULL)
            tmp->grp = grp->gr_name;
    tmp->mtime = sb.st_mtimespec;
    tmp->time = get_time(tmp->mtime.tv_sec);
    tmp->name = ft_strdup(av);
    tmp->next = NULL;
    tmp->size = sb.st_size;
    tmp->blocks = sb.st_nlink;
    tmp->rights = get_rights(sb);
    tmp->dirr = get_type(sb);
    tmp->inside = NULL;
    return (tmp);
}

void    add_back(t_lst **s, char *ac , struct stat sb)
{
    t_lst *tmp;

    tmp = *s;
    if (!tmp)
    {
        *s = get_arg(ac, sb);
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = get_arg(ac, sb);
}

void   ft_list_swap(t_lst **current)
{
    t_lst  *tmp;

    tmp = (*current)->next->next;
    (*current)->next->next = (*current);
    (*current)->next = tmp;
}

void    sort_ascii(t_lst **begin_list)
{
    t_lst  *current;
    t_lst  *last;

    current = *begin_list;
    if (!*begin_list)
        return ;
    while (current->next)
    {
        if (ft_strcmp(current->name, current->next->name) > 0)
        {
            if (current != *begin_list)
                last->next = current->next;
            else
                *begin_list = current->next;
            ft_list_swap(&current);
            current = *begin_list;
        }
        else
        {
            last = current;
            current = current->next ? current->next : current;
        }
    }
}

void    sort_reverse(t_lst **begin_list)
{
    t_lst  *current;
    t_lst  *last;

    current = *begin_list;
    if (!*begin_list)
        return ;
    while (current->next)
    {
        if (ft_strcmp(current->name, current->next->name) < 0)
        {
            if (current != *begin_list)
                last->next = current->next;
            else
                *begin_list = current->next;
            ft_list_swap(&current);
            current = *begin_list;
        }
        else
        {
            last = current;
            current = current->next ? current->next : current;
        }
    }
}
