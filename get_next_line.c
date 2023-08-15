/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:59:37 by mohamoha          #+#    #+#             */
/*   Updated: 2023/08/15 19:56:55 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*dequeue_until_newlin(t_queue *q)
{
	t_queue_node	*current;
	int				length;
	int				i;
	char			*line;

	if (q->front == NULL)
		return (NULL);
	current = q->front;
	length = 0;
	while (current && current->val != '\n')
	{
		length++;
		current = current->next;
	}
	line = (char *)malloc(sizeof(char) * (length + 2));
	i = 0;
	while (q->front && q->front->val != '\n')
		line[i++] = dequeue(q);
	line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

char	*dequeue_last_line(t_queue *q)
{
	t_queue_node	*current;
	int				length;
	int				i;
	char			*line;

	if (q->front == NULL)
		return (NULL);
	current = q->front;
	length = 0;
	while (current)
	{
		length++;
		current = current->next;
	}
	line = (char *)malloc(sizeof(char) * (length + 1));
	i = 0;
	while (q->front && q->front->val != '\n')
		line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

int	contains_newline(t_queue *q)
{
	struct s_queue_node	*tmp;

	tmp = q->front;
	while (tmp)
	{
		if (tmp->val == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*handle_bytes(ssize_t bytes, t_queue *q, char *buffer, int *fd)
{
	if (bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(buffer);
		if (queue_is_empty(q))
			return (NULL);
		else
			return (dequeue_last_line(q));
	}
	else
	{
		enqueue(q, buffer, bytes);
		free(buffer);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	static t_queue	q;
	ssize_t			bytes;
	char			*buffer;
	char			*clear;
	static int		flag = 0;

	if (fd == -1)
		return (NULL);
	if (flag == 0)
	{
		q.front = NULL;
		q.rear = NULL;
		flag = 1;
	}
	if (!queue_is_empty(&q) && contains_newline(&q))
		return (dequeue_until_newlin(&q));
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		clear = dequeue_all(&q);
		free(clear);
	}
	return (handle_bytes(bytes, &q, buffer, &fd));
}

/*int main() {
    int fd = open("sample.txt", O_RDONLY); // Replace with your file name

    char *line = get_next_line(fd);
    // int i = 1;

	printf("Line: %s", line);
    // while ((line = get_next_line(fd)) != NULL) {
    //     printf("Line[%d]: %s", i, line);
    //     free(line);
    //     i++;
    // }
    close(fd);
    return 0;
}*/