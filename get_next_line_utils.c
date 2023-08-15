/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:59:25 by mohamoha          #+#    #+#             */
/*   Updated: 2023/08/15 19:55:47 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	queue_is_empty(t_queue *q)
{
	return (q->front == NULL);
}

int	queue_length(t_queue *q)
{
	int				length;
	t_queue_node	*current;

	length = 0;
	current = q->front;
	while (current)
	{
		length++;
		current = current->next;
	}
	return (length);
}

void	enqueue(t_queue *q, const char *buffer, size_t bytes_read)
{
	t_queue_node	*new_node;
	size_t			i;

	i = 0;
	while (i < bytes_read)
	{
		new_node = (t_queue_node *)malloc(sizeof(t_queue_node));
		new_node->val = buffer[i];
		new_node->next = NULL;
		if (q->front == NULL)
		{
			q->front = new_node;
			q->rear = new_node;
		}
		else
		{
			q->rear->next = new_node;
			q->rear = new_node;
		}
		i++;
	}
}

char	dequeue(t_queue *q)
{
	t_queue_node	*tmp;
	char			value;

	if (q->front == NULL)
		return ('\0');
	tmp = q->front;
	q->front = q->front->next;
	value = tmp->val;
	free(tmp);
	if (q->front == NULL)
		q->rear = NULL;
	return (value);
}

char	*dequeue_all(t_queue *q)
{
	char	*line;
	int		length;
	int		i;
	char	c;

	length = queue_length(q);
	line = (char *)malloc(length + 1);
	i = 0;
	while (!queue_is_empty(q))
	{
		c = dequeue(q);
		line[i++] = c;
	}
	line[length] = '\0';
	return (line);
}
