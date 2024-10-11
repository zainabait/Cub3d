/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohilloc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:40:01 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/11 18:26:24 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	clearheap(t_heap **node)
{
	t_heap	*tmp;

	if (!node || !*node)
		return ;
	tmp = *node;
	while (node && *node)
	{
		free(tmp->ptr);
		tmp->ptr = NULL;
		tmp = tmp->next;
		free(*node);
		*node = tmp;
	}
}

void	heap_addback(t_heap **lst, t_heap *new)
{
	t_heap	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_heap	*heap_new(void *content)
{
	t_heap	*head;

	head = (t_heap *)malloc(sizeof(t_heap));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}

t_data	*get_cub(t_data *cub)
{
	static t_data	*cub_s;

	if (cub)
		cub_s = cub;
	return (cub_s);
}

void	*talloc(size_t __size)
{
	void	*__ptr;
	t_heap	*__node;
	t_data	*__cub;

	__cub = get_cub(NULL);
	__ptr = malloc(__size);
	if (__ptr == NULL)
	{
		clearheap(&__cub->heap);
		ft_error_message("Error: malloc failed");
	}
	__node = heap_new(__ptr);
	if (!__node)
	{
		free(__ptr);
		clearheap(&__cub->heap);
		ft_error_message("Error: malloc failed");
	}
	heap_addback(&__cub->heap, __node);
	return (__ptr);
}
