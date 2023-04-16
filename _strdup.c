#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: pointer to string to be duplicated
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	char		*str_cpy;
	unsigned int i;
	unsigned int len = 0;

	if (str == NULL) /* return null if string is null */
		return (NULL);

	while (str[len] != '\0') /* find length of string */
		len++;

	str_cpy = malloc((len + 1) * sizeof(char));

	if (str_cpy == NULL) /* return null on allocation fail */
		return (NULL);

	for (i = 0; i < len; i++) /*duplicate content from str into copy*/
		str_cpy[i] = str[i];
	str_cpy[i] = '\0';

	return (str_cpy);
}

