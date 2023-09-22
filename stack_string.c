#include "monty.h"

/**
 * print_char - Prints the Ascii value.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @l_number: Interger representing the line number of of the opcode.
 */
void print_char(stack_t **stack, unsigned int l_number)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		string_err(11, l_number);

	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		string_err(10, l_number);
	printf("%c\n", ascii);
}

/**
 * print_str - Prints a string.
 * @s: Pointer to a pointer pointing to top node of the stack.
 * @ln: Interger representing the line number of of the opcode.
 */
void print_str(stack_t **s, __attribute__((unused))unsigned int ln)
{
	int ascii;
	stack_t *tmp;

	if (s == NULL || *s == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *s;
	while (tmp != NULL)
	{
		ascii = tmp->n;
		if (ascii <= 0 || ascii > 127)
			break;
		printf("%c", ascii);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the first node of the stack to the bottom.
 * @s: Pointer to a pointer pointing to top node of the stack.
 * @ln: Interger representing the line number of of the opcode.
 */
void rotl(stack_t **s, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (s == NULL || *s == NULL || (*s)->next == NULL)
		return;

	tmp = *s;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *s;
	(*s)->prev = tmp;
	*s = (*s)->next;
	(*s)->prev->next = NULL;
	(*s)->prev = NULL;
}


/**
 * rotr - Rotates the last node of the stack to the top.
 * @s: Pointer to a pointer pointing to top node of the stack.
 * @ln: Interger representing the line number of of the opcode.
 */
void rotr(stack_t **s, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (s == NULL || *s == NULL || (*s)->next == NULL)
		return;

	tmp = *s;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *s;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*s)->prev = tmp;
	(*s) = tmp;
}

