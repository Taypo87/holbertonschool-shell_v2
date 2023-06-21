#include "header.h"

int set_env(EnvNode **top, char *key, char *value)
{
    EnvNode *current = *top;
    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0)
        {
            free(current->value);
            current->value = copy_string(value);
            return (1);
        }
        current = current->next;
    }
    EnvNode *node = create_kv_node(key, value);
    add_node_to_list(top, node);
    return (1);
}

char* get_env(EnvNode *top, char *key)
{
    EnvNode *current = top;
    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0)
        {
            return (current->value);
        }
        current = current->next;
    }
    return (NULL);
}

int unset_env(EnvNode **top, char *key)
{
    EnvNode *current = *top;
    EnvNode *prev = NULL;

    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0) {
            if (prev == NULL) {
                *top = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return (1);
        }
        prev = current;
        current = current->next;
    }
    return (1);
}
