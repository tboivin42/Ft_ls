/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 08:39:39 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/19 19:04:22 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <locale.h>
# include <langinfo.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# define FLAG_L 1
# define FLAG_LR 2
# define FLAG_A 4
# define FLAG_T 8
# define FLAG_UR 16

typedef struct		s_opt
{
	int				s;
	int				l;
	int				n;
	int				i;
	int				j;
	int				y;
	int				k;
	int				r;
	int				o;
	char			*test;
	char			*path;
	char			*str;
	char			dirr;
	int				ac_i;
	char			**ac;
	char			*rights;
	int				av;
	struct group	*grp;
	struct passwd	*pwd;
	struct stat		sb;
	struct dirent	*tmp;

}					t_opt;

typedef struct		s_lst
{
	size_t			blocks2;
	char			*path;
	long			size;
	struct timespec	mtime;
	char			*pw;
	char			*rights;
	char			*grp;
	char			*time;
	char			type;
	int				minor;
	int				major;
	long			blocks;
	char			*name;
	struct s_lst	*next;
	struct s_lst	*inside;
}					t_lst;

void				print_recur(t_lst *dir, t_opt *s);
void				count_size(t_lst *dir, t_opt *s);
void				print_recur(t_lst *dir, t_opt *s);
void				print_long_2(t_lst *dir, t_opt *s);
int					cmp_time(t_lst *l1, t_lst *l2);
int					cmp_alpha(t_lst *elem1, t_lst *elem2);
void				sort(t_lst **list, int (*cmp)(t_lst *elem1, t_lst *elem2));
void				sort_time(t_lst **begin_list);
void				print_long_(t_lst *tmp, t_lst *dir, t_opt *s);
void				print_long(t_lst *files, t_opt *s);
void				print_inside(t_lst *dir, t_opt *s);
void				recur(t_lst **dir, t_opt *s);
void				order(t_lst **dir, t_lst **files, t_opt *s);
char				*get_time(struct timespec mtime);
char				*get_rights(struct stat sb);
void				sort_reverse(t_lst **begin_list);
void				no_such(char *s);
char				get_type(struct stat sb);
void				arg(t_lst **err, t_lst **files, t_lst **dir, t_opt *s);
void				check_arg(t_opt *s);
t_opt				*set_opt(int ac, char **av);
t_lst				*set_lst(void);
void				get_flags(t_opt *s);
void				add_back(t_lst **new, char *ac, struct stat sb, t_opt *s);
t_lst				*get_arg(char *av, struct stat sb, t_opt *s);
void				print_order(t_lst *err, t_lst *files, t_opt *s);
void				no_options(char c);
void				check(t_opt *s, char **av);
void				ls(t_lst **dir, t_opt *s);

#endif
