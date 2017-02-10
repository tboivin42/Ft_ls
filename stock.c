/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 02:59:37 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/28 02:59:39 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void 	arg(t_parse *parse, t_opt *s)
{
    while (s->ac[s->i])
    {
        if (stat(s->ac[s->i], &s->sb) == -1)
            add_back(&parse->err, s->ac[s->i], s->sb);
        else
        {
            if (s->sb.st_mode & S_IFDIR)
                add_back(&parse->dir, s->ac[s->i], s->sb);
            else
               	add_back(&parse->files, s->ac[s->i], s->sb);
        }
        s->i++;
    }
}
