/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 08:39:39 by tboivin           #+#    #+#             */
/*   Updated: 2017/01/26 19:11:39 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS
# define FLAG_L 1
# define FLAG_LR 2
# define FLAG_A 4
# define FLAG_T 8
# define FLAG_UR 16

#include "../../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct          s_opt
{
    int             n;
    int             i;
    int             j;
    int             k;
    int             o;
    char            *path;
    char            dirr;
    int             ac_i;
    char            **ac;
    char            *rights;
    int             av;
    struct stat     sb;
    struct dirent   *tmp;

}                       t_opt;

typedef struct          s_lst
{

    long            size;
    struct timespec mtime;
    char            *pw;
    char            *rights;
    char            *grp;
    char            *time;
    char            dirr;
    long            blocks;
    char            *name;
    struct s_lst    *next;
    struct s_lst    *inside;
}                       t_lst;

typedef struct           s_parse
{
    t_lst *dir;
    t_lst *err;
    t_lst *files;
}                        t_parse;

void    print_long(t_parse *parse);
void    print_inside(t_parse *parse, t_opt *s);
void    recur(t_parse *parse, t_opt *s, int av, char **ac);
void    order(t_parse *parse, t_opt *s);
char    *get_time(long mtime);
void    order(t_parse *parse, t_opt *s);
void    ls_f(t_parse *parse, t_opt *s);
char    *get_rights(struct stat sb);
void    sort_reverse(t_lst **begin_list);
void    get_info(t_parse *parse, t_opt *s, struct stat sb);
void    no_such(char *s);
char    get_type(struct stat sb);
void    arg(t_parse *parse, t_opt *s);
void        check_arg(t_opt *s);
t_opt       *set_opt(int ac, char **av);
t_lst   *set_lst(void);
void        get_flags(t_opt *s);
void    add_back(t_lst **s, char *ac, struct stat sb);
t_lst   *get_arg(char *av, struct stat sb);
void    sort_ascii(t_lst **begin_list);
void    print_order(t_parse *parse, t_opt *s);
void    no_options(char c);
void    check(t_opt *s, char **av);
void    ls(t_lst **dir, t_opt *s);

#endif