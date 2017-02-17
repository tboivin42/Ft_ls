/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 23:40:19 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:17:15 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	get_type(struct stat sb)
{
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((sb.st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if (S_ISCHR(sb.st_mode))
		return ('c');
	if (S_ISBLK(sb.st_mode))
		return ('b');
	if ((sb.st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('?');
}

char	*get_rights(struct stat sb)
{
	char *str;

	str = ft_strnew(10);
	str[0] = ((sb.st_mode & S_IRUSR) ? 'r' : '-');
	str[1] = ((sb.st_mode & S_IWUSR) ? 'w' : '-');
	str[2] = ((sb.st_mode & S_IXUSR) ? 'x' : '-');
	str[3] = ((sb.st_mode & S_IRGRP) ? 'r' : '-');
	str[4] = ((sb.st_mode & S_IWGRP) ? 'w' : '-');
	str[5] = ((sb.st_mode & S_IXGRP) ? 'x' : '-');
	str[6] = ((sb.st_mode & S_IROTH) ? 'r' : '-');
	str[7] = ((sb.st_mode & S_IWOTH) ? 'w' : '-');
	str[8] = ((sb.st_mode & S_IXOTH) ? 'x' : '-');
	return (str);
}
