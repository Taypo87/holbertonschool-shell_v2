#include "lists.h"

/**
 * add_nodeint - adds a node to the begining of a list
 * @head: address of the first node in the list
 * @n: int to be copied to new list
 * Return: address of the new element
 */

listint_t *add_nodeint(listint_t **head, const int n)

{
	listint_t *new;

	new = malloc(sizeof(listint_t));

	if (new == NULL)
	{
		free(new);
		return (NULL);
	}

	new->n = n;
	new->next = *head;
	*head = new;

	return (new);
}
