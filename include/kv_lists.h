#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct list_s - singly linked list node structure for two strings
 * @key: the string to be assosiated with the value
 * @value: the string that's really of interest to us
 * @next: points to the next node
 *
 * Description: Used instead of a hash table to store key, value pairs
 * because the order of the nodes is important.
 */
typedef struct kv_list_s
{
	char *key;
	char *value;
	struct list_s *next;
} kv_list_t;

kv_list_t *create_kv_node(char *key, char *value);
void free_kvlist(kv_list_t **top);

#endif
