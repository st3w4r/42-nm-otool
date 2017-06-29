/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:06:39 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:30:04 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Sort by insertion
*/

void				insert_archive_before(t_s_archive_list *s1,
										t_s_archive_list *s2)
{
	s2->next = s1;
	s2->prev = s1->prev;
	s1->prev = s2;
	if (s2->prev)
	{
		s2->prev->next = s2;
	}
}

void				insert_archive_after(t_s_archive_list *s1,
										t_s_archive_list *s2)
{
	s2->next = s1->next;
	s2->prev = s1;
	s1->next = s2;
	if (s2->next)
	{
		s2->next->prev = s2;
	}
}

void				set_format_archive_list(t_s_format *format,
										t_s_archive_list *archive_elem)
{
	while (archive_elem->prev != NULL)
	{
		archive_elem = archive_elem->prev;
	}
	format->archive_list = archive_elem;
}

t_s_archive_list	*add_archive(t_s_format *format,
								t_s_archive_list *archive_elem)
{
	t_s_archive_list *archive_list;
	t_s_archive_list *archive_prev;

	archive_list = format->archive_list;
	while (archive_list != NULL)
	{
		if (ft_strcmp(archive_elem->name, archive_list->name) < 0)
		{
			insert_archive_before(archive_list, archive_elem);
			set_format_archive_list(format, archive_elem);
			return (archive_elem);
		}
		archive_prev = archive_list;
		archive_list = archive_list->next;
	}
	insert_archive_after(archive_prev, archive_elem);
	set_format_archive_list(format, archive_elem);
	return (archive_elem);
}

/*
** Add symbol to the archive_list
** Send a struct nlist and receive a struct archive_list
** Init if the format archive_list is null
*/

t_s_archive_list	*add_archive_list(t_s_format *format,
									void *ar_object,
									char *name)
{
	t_s_archive_list *archive_elem;

	if ((archive_elem = malloc(sizeof(t_s_archive_list))) == NULL)
		ft_malloc_error();
	archive_elem->ar_object = ar_object;
	archive_elem->name = name;
	archive_elem->next = NULL;
	archive_elem->prev = NULL;
	if (format->archive_list == NULL)
		set_format_archive_list(format, archive_elem);
	else
		add_archive(format, archive_elem);
	return (archive_elem);
}
