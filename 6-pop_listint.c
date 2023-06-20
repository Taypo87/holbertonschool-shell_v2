#include "lists.h"

/**
 * pop_listint - deletes the head node of a list
 * @head: pointer to the address of the first node in list
 * Return: data of node removed, or 0 if failed
 */

int pop_listint(listint_t **head)
{
	listint_t *tmp;
	int ret;

	if (*head == NULL)
		return (0);

	tmp = *head;
	ret = (*head)->n;
	*head = (*head)->next;

	free(tmp);

	return (ret);
}
