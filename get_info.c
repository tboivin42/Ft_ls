/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 23:40:19 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/19 16:07:36 by tboivin          ###   ########.fr       */
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

char	get_two(struct stat sb)
{
	char	two;

	if (sb.st_mode & S_IXUSR)
		two = 'x';
	else
		two = '-';
	if (sb.st_mode & S_ISUID)
	{
		if (sb.st_mode & 0100)
			two = 's';
		else
			two = 'S';
	}
	return (two);
}

char	get_five(struct stat sb)
{
	char	five;

	if (sb.st_mode & S_IXGRP)
		five = 'x';
	else
		five = '-';
	if (sb.st_mode & S_ISGID)
	{
		if (sb.st_mode & 0010)
			five = 's';
		else
			five = 'S';
	}
	return (five);
}

char	get_eight(struct stat sb)
{
	char	eight;

	if (sb.st_mode & S_IXOTH)
		eight = 'x';
	else
		eight = '-';
	if (sb.st_mode & S_ISVTX)
	{
		if (sb.st_mode & 0100)
			eight = 't';
		else
			eight = 'T';
	}
	return (eight);
}

char	*get_rights(struct stat sb)
{
	char *str;

	str = ft_strnew(10);
	str[0] = ((sb.st_mode & S_IRUSR) ? 'r' : '-');
	str[1] = ((sb.st_mode & S_IWUSR) ? 'w' : '-');
	str[2] = get_two(sb);
	str[3] = ((sb.st_mode & S_IRGRP) ? 'r' : '-');
	str[4] = ((sb.st_mode & S_IWGRP) ? 'w' : '-');
	str[5] = get_five(sb);
	str[6] = ((sb.st_mode & S_IROTH) ? 'r' : '-');
	str[7] = ((sb.st_mode & S_IWOTH) ? 'w' : '-');
	str[8] = get_eight(sb);
	return (str);
}
