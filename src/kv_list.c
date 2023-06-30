#include "kv_lists.h"

static kv_list_t *create_kv_node(char *key, char *value);
static void place_node_on_kvlist(kv_list_t **top, kv_list_t *node);

/**
 * add_kv_node - addes a node containing key, value node to linked list
 * @head: Double pointer to the current head of the list (if there is one)
 * @k: the string used that we need to assosiate with the 'real' value
 * @v: the value that we're really interested in.
 *
 * Return: A single pointer to the new node
*/
kv_list_t *add_kv_node(kv_list_t **head, char *k, char *v)
{
	kv_list_t *new_node = NULL;

	new_node = create_kv_node(k, v);

	if (new_node == NULL)
		return (NULL);

	place_node_on_kvlist(head, new_node);

	return (new_node);
}

/**
 * create_kv_node - initalizes the value of new node
 * @key:the string used that we need to assosiate with the 'real' value
 * @value: the value that we're really interested in.
 *
 * Return: Pointer to the new node
*/
static kv_list_t *create_kv_node(char *key, char *value)
{
	kv_list_t *new_node = (kv_list_t *)malloc(sizeof(kv_list_t));

	new_node->key = copy_string(key);
	new_node->value = copy_string(value);
	new_node->next = NULL;

	return (new_node);
}

/**
 * place_node_on_kvlist- places a new node at the end of kvlist
 * @top: double pointer to the tope of the list
 * @node: the node that needs to be place at the end
*/
static void place_node_on_kvlist(kv_list_t **top, kv_list_t *node)
{
	kv_list_t *current;

	if (*top == NULL)
		*top = node;
	else
	{
		current = *top;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}

/**
 * free_kvlist - decllocates the nodes of singly linked kv list from top
 * @top: the top of a singly linked list of key, value pairs
*/
void free_kvlist(kv_list_t **top)
{
	kv_list_t *current = *top;
	kv_list_t *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*top = NULL;
}
