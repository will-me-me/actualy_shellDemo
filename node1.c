#include "shell.h"

/**
 * add_list_node - a function that adds a node to the start of the list
 * @list_head: address of pointer to head node
 * @s: s field of node
 * @num: node index used by history
 * Return: returns the size of list
 */
list_t *add_list_node(list_t **list_head, const char *s, int num)
{
	list_t *new_head;

	if (!list_head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	fill_memory_with_char((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (s)
	{
		new_head->str = duplicate_string_memory(s);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *list_head;
	*list_head = new_head;
	return (new_head);
}

/**
 * append_list_node - adds a node to the end of the list
 * @list_head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *append_list_node(list_t **list_head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	fill_memory_with_char((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = duplicate_string_memory(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}

/**
 * print_string_elements - a function that prints only the str element of a list_t
 * @head: pointer to first node
 * Return: returns the size of list
 */
size_t print_string_elements(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		string_puts(head->str ? head->str : "(nil)");
		string_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - a function that deletes node at given index
 * @list_head: address of pointer to first node
 * @index: index of node to delete
 * Return: returns 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **list_head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!index)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *list_head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * clear_linked_list - a function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: returns void
 */
void clear_linked_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

