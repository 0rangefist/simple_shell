#include <stdlib.h>

/**
 * _strcmp - compare two strings
 *
 * @s1: pointer to the first string to be compared
 * @s2: pointer to the second string to be compared
 *
 * Return: an int greater than, equal to, or less than 0.
 */
int _strcmp(const char *s1, const char *s2)
{
	int result;

	while (*s1 != '\0' && *s2 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	result = *(const unsigned char *) s1 - *(const unsigned char *) s2;

	return (result);
}

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
