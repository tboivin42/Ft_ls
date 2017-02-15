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
    int             y;
    int             k;
    int             r;
    int             o;
    char            *test;
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
    char            *path;
    long            size;
    struct timespec mtime;
    char            *pw;
    char            *rights;
    char            *grp;
    char            *time;
    char            type;
    long            blocks;
    char            *name;
    struct s_lst    *next;
    struct s_lst    *inside;
}                       t_lst;

void    print_long_2(t_lst *dir);
int         cmp_time(t_lst *l1, t_lst *l2);
int         cmp_alpha(t_lst *elem1, t_lst *elem2);
void        sort(t_lst **list, int (*cmp)(t_lst *elem1, t_lst *elem2));
// void   ft_list_swap(t_lst **current);
void    sort_time(t_lst **begin_list);
void    print_long_(t_lst *dir, t_opt *s);
void    print_long(t_lst *files);
void    print_inside(t_lst *dir, t_opt *s);
void    recur(t_lst **dir, t_opt *s);
void    order(t_lst *dir, t_lst *files, t_opt *s);
char    *get_time(struct timespec mtime);
char    *get_rights(struct stat sb);
void    sort_reverse(t_lst **begin_list);
// void    get_info(t_parse *parse, t_opt *s, struct stat sb);
void    no_such(char *s);
char    get_type(struct stat sb);
void    arg(t_lst **err, t_lst **files, t_lst **dir, t_opt *s);
void        check_arg(t_opt *s);
t_opt       *set_opt(int ac, char **av);
t_lst   *set_lst(void);
void        get_flags(t_opt *s);
void    add_back(t_lst **new, char *ac, struct stat sb, t_opt *s);
t_lst   *get_arg(char *av, struct stat sb, t_opt *s);
// void    sort_ascii(t_lst **begin_list);
void    print_order(t_lst *err, t_lst *files, t_opt *s);
void    no_options(char c);
void    check(t_opt *s, char **av);
void    ls(t_lst **dir, t_opt *s);

#endif