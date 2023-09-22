#include "monty.h"

/**
 * open_file - opens a file
 * @f_name: the file namepath
 * Return: void
 */

void open_file(char *f_name)
{
	FILE *fd = fopen(f_name, "r");

	if (f_name == NULL || fd == NULL)
		err(2, f_name);

	read_file(fd);
	fclose(fd);
}


/**
 * read_file - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void read_file(FILE *fd)
{
	int l_number, format = 0;
	char *buffer = NULL;
	size_t le = 0;

	for (l_number = 1; getline(&buffer, &le, fd) != -1; l_number++)
	{
		format = parse_line(buffer, l_number, format);
	}
	free(buffer);
}


/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @bf: line from the file
 * @li_number: line number
 * @f:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_line(char *bf, int li_number, int f)
{
	char *opcode, *v;
	const char *delim = "\n ";

	if (bf == NULL)
		err(4);

	opcode = strtok(bf, delim);
	if (opcode == NULL)
		return (f);
	v = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, v, li_number, f);
	return (f);
}

/**
 * find_func - find the appropriate function for the opcode
 * @opcode: opcode
 * @v: argument of opcode
 * @f:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_func(char *opcode, char *v, int ln, int f)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, opcode, v, ln, f);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * call_fun - Calls the required function.
 * @my_func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @f: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func my_func, char *op, char *val, int ln, int f)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (f == 0)
			my_func(&node, ln);
		if (f == 1)
			add_to_queue(&node, ln);
	}
	else
		my_func(&head, ln);
}

