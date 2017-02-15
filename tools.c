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

t_lst   *get_arg(char *av, struct stat sb, t_opt *s)
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

void    add_back(t_lst **new, char *ac , struct stat sb, t_opt *s)
{
    t_lst *tmp;

    tmp = *new;
    if (!tmp)
    {
        *new = get_arg(ac, sb, s);
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = get_arg(ac, sb, s);
}

void    sort_reverse(t_lst **list)
{
    t_lst   *tmp;
    t_lst   *tmp2;
    t_lst   *tmp3;

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

void        elem_cpy(t_lst **src, t_lst *cpy)
{
    (*src)->name = cpy->name;
    (*src)->path = cpy->path;
    (*src)->size = cpy->size;
    (*src)->pw = cpy->pw;
    (*src)->grp = cpy->grp;
    (*src)->time = cpy->time;
    (*src)->blocks = cpy->blocks;
    (*src)->mtime = cpy->mtime;
    (*src)->type = cpy->type;
    (*src)->rights = cpy->rights;
}

void        swap_elem(t_lst **a, t_lst **b)
{
    t_lst tmp;

    tmp = **a;
    elem_cpy(a, *b);
    elem_cpy(b, &tmp);
}

int         cmp_alpha(t_lst *elem1, t_lst *elem2)
{
    return (ft_strcmp(elem1->name, elem2->name));
}

void        sort(t_lst **list, int (*cmp)(t_lst *elem1, t_lst *elem2))
{
    t_lst *a;
    t_lst *b;

    a = *list;
    while (a)
    {
        b = a->next;
        while (b)
        {
            if (cmp(a, b) > 0)
                swap_elem(&a, &b);
            b = b->next;
        }
        a = a->next;
    }
}
