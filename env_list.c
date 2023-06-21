#include "header.h"

EnvNode* load_env(char **envp)
{
	EnvNode *top = NULL, *node;
	char *key, *value;
	int i = 0;
	while (envp[i] != NULL)
	{
		key = strtok(envp[i], "=");
		value = strtok(NULL, "\n");
		node = create_kv_node(key, value);
		add_node_to_list(&top, node);
		i++;
	}
	return (top);
}

EnvNode* create_kv_node(char *key, char *value)
{
	EnvNode *node = (EnvNode *)malloc(sizeof(EnvNode));
	node->key = copy_string(key);
	node->value = copy_string(value);
	node->next = NULL;

	return (node);
}

void add_node_to_list(EnvNode **top, EnvNode *node)
{
	EnvNode *current;

	if (*top == NULL)
	{
		*top = node;
	}
	else
	{
		current = *top;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
	}
}

void free_env_list(EnvNode **top)
{
	EnvNode *current = *top;

	while (current != NULL)
	{
		EnvNode *next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*top = NULL;
}