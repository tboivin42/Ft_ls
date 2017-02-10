/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 20:52:17 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/26 19:36:29 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void    opt(t_opt *s, char **ac)
{
    if (ac[s->i][s->j] == 'l')
        s->o = s->o | FLAG_L;
    else if (ac[s->i][s->j] == 'r')
        s->o = s->o | FLAG_LR;
    else if (ac[s->i][s->j] == 'a')
        s->o = s->o | FLAG_A;
    else if (ac[s->i][s->j] == 't')
        s->o = s->o | FLAG_T;
    else if (ac[s->i][s->j] == 'R')
        s->o = s->o | FLAG_UR;
    else
        no_options(ac[s->i][s->j]);
    s->j++;
    if (ac[s->i][s->j] == '-')
        opt(s, ac);
    check(s, ac);
}

void    check(t_opt *s, char **ac)
{
    if (ac[s->i][s->j] != '\0')
    {
        if (ac[s->i][s->j] == 'l' || ac[s->i][s->j] == 'r' || 
            ac[s->i][s->j] == 'a' || ac[s->i][s->j] == 't' || ac[s->i][s->j] == 'R')
            opt(s, ac);
        else 
        {
            if (ac[s->i][s->j] == '-')
            {
                s->ac[s->av + 1] = ".";
                return ;
            }
            if (ac[s->i][s->j] != '-')
                opt(s, ac);
            if (ac[s->i][s->j + 1] != '\0')
                no_options(ac[s->i][s->j]);
        }
    }
}

void    check_arg(t_opt *s)
{
    while(s->i < s->av)
    {
        if (s->ac[s->i][s->j] == '-' && s->ac[s->i][s->j + 1] != '\0')
        {
            s->k++;
            s->j++;
            check(s, s->ac);
        }
        else
            return ;
        s->j = 0;
        s->i++;
    }
}