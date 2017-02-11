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

int     main(int av, char **ac)
{
    t_opt *s;
    t_parse parse;
    t_lst *begin_list;

    begin_list = NULL;
    parse.dir = NULL;
    parse.files = NULL;
    parse.err = NULL;
    s = set_opt(av, ac);
    if (av > 1)
    {
    	check_arg(s);
    	arg(&parse, s);
    }
    sort_ascii(&parse.err);
    if(!s->ac[s->k])
    {
        s->k -= 1;
        s->i = s->i - 1;
        s->ac[s->i] = ft_strdup(".");
        arg(&parse, s);
    }
    if (parse.dir)
    {
        begin_list = parse.dir;
        ls(&parse.dir, s);
        parse.dir = begin_list;
    }
    // if (s->o & FLAG_UR)
    //     recur(&parse, s, av, ac);
    print_order(&parse, s);
    return (0);
}
