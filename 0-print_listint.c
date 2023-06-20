#include "lists.h"

/**
 * print_listint - iterates through and prints each nodes content
 * @h: a pointer to the list to print
 * Return: number of nodes in the list
 */

size_t print_listint(const listint_t *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		printf("%d\n", h->n);
		h = h->next;
	}

	return (count);
}
