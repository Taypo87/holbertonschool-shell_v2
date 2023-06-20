#include "lists.h"

/**
 * free_listint2 - frees a list and sets the head pointer to NULL
 * @head: pointer to the begining of the list
 * Return: Void
 */

void free_listint2(listint_t **head)

{
	listint_t *tmp;

	if (head == NULL)
		return;

	while (*head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}

	head = NULL;
}
