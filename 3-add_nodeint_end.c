#include "lists.h"

/**
 * add_nodeint_end - adds a node to the end of list listint_t
 * @head: address of the first element in list
 * @n: the int to be copied into new node
 * Return: address of the new node
 */

listint_t *add_nodeint_end(listint_t **head, const int n)

{
	listint_t *new, *last;

	new = malloc(sizeof(listint_t));

	if (new == NULL)
	{
		free(new);
		return (NULL);
	}

	new->n = n;
	new->next = NULL;

	if (*head == NULL)
		*head = new;

	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	return (*head);
}
