#include "shell.h"

/**
 * free_array - Frees the memory used by an array of strings
 *
 * @arr: The array of strings to free
 */
void free_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

/**
 * free_2d_array - Frees the memory used by a 2D array of strings
 *
 * @arr: The 2D array of strings to free
 */
void free_2d_array(char ***arr)
{
	int i, j;

	for (i = 0; arr[i] != NULL; i++)
	{
		for (j = 0; arr[i][j] != NULL; j++)
		{
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);
}
