#include "lists.h"

/**
 * sum_listint - adds the value stored in each node
 * @head: the address of the first node in the list
 * Return: the sum of values stored, or zero if the list is NULL
 */

int sum_listint(listint_t *head)
{
	int sum = 0;

	if (head == NULL)
		return (0);

	while (head)
	{
		sum += head->n;
		head = head->next;
	}

	return (sum);
}
