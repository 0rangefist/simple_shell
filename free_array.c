#include "shell.h"

/**
 * free_array - Frees the memory used by an array of strings
 *
 * @str_arr: The array of strings to free
 */
void free_array(char **str_arr)
{
	int i;

	for (i = 0; str_arr[i] != NULL; i++)
	{
		free(str_arr[i]);
	}
	free(str_arr);
}
