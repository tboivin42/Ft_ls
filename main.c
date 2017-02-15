/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 03:27:29 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/26 19:12:17 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void    main_(t_lst *err, t_lst *files, t_lst *dir, t_opt *s)
{
    t_lst *begin_list;

    begin_list = NULL;
    if (dir)
    {
        begin_list = dir;
        ls(&dir, s);
        dir = begin_list;
    }
    if (s->o & FLAG_UR)
        recur(&dir->inside, s);
    else
    {
        order(dir, files, s);
        print_inside(dir, s);
        print_order(err, files, s);
    }
}

int     main(int av, char **ac)
{
    t_opt *s;
    t_lst *dir;
    t_lst *files;
    t_lst *err;

    dir = NULL;
    files = NULL;
    err = NULL;
    s = set_opt(av, ac);
    if (av > 1)
    {
    	check_arg(s);
    	arg(&err, &files, &dir, s);
    }
    if (err)
        sort(&err, cmp_alpha);
    if(!s->ac[s->k])
    {
        s->k -= 1;
        s->i = s->i - 1;
        s->ac[s->i] = ft_strdup(".");
        arg(&err, &files, &dir, s);
    }
    main_(err, files, dir, s);
    return (0);
}
