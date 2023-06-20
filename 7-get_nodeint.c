#include "lists.h"

/**
 * get_nodeint_at_index - finds a given node in a list
 * @head: a pointer to the head of the list
 * @index: the index of the node to find
 * Return: the located node, or NULL if it does not exist
 */

listint_t *get_nodeint_at_index(listint_t *head, unsigned int index)
{
	unsigned int count;

	for (count = 0; count < index; count++)
	{
		if (head == NULL)
			return (NULL);

		head = head->next;
	}

	return (head);
}
