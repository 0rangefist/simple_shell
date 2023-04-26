#include <stdlib.h>

/**
 * _strcat -  concatenates two strings
 *
 * @dest: pointer to destination string
 * @src: pointer to source string
 *
 * Return: pointer to resulting destination string
 */
char *_strcat(char *dest, char *src)
{
	char *dest_ptr;
	char *src_ptr;

	dest_ptr = dest;
	src_ptr	 = src;

	/* Move the pointer up to the point where the null terminator is*/
	while (*dest_ptr != '\0')
	{
		dest_ptr++;
	}

	/* Iterate through src_ptr, copying each value over to *dest_ptr, */
	/* which now has it's starting point where it's null terminator is */
	while (*src_ptr != '\0')
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
	}

	/* We add a null terminator at the end of dest using dest_ptr */
	*dest_ptr = '\0';

	return (dest);
}

/**
 * _strncmp - compares two strings up to n characters
 *
 * @str1: first pointer to string
 * @str2: second pointer to string
 * @n: number of characters to compare
 *
 * Return: negative, 0, or positive integer if s1 is less than, equal to,
 * or greater than s2, respectively, up to n characters.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{

	while (n > 0 && *str1 != '\0' && *str2 != '\0' && (*str1 == *str2))
	{
		str1++;
		str2++;
		n--;
	}

	if (n == 0)
		return (0);
	else
		return (*str1 - *str2);
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

/**
 * _strlen - Calculates the length of a string
 *
 * @str: Pointer to the string to be measured
 *
 * Return: The length of the string
 */
int _strlen(char *str)
{
	int count = 0;

	while (str[count] != '\0')
	{
		count++;
	}

	return (count);
}

/**
 * _strncpy - copies a string from src to dest
 *
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: num of chars of src to use
 *
 * Return: pointer to resulting destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *dest_ptr;
	char *src_ptr;

	dest_ptr = dest;

	/* Iterate through src_ptr n times, copying each value over to *dest_ptr*/
	for (src_ptr = src; n > 0 && *src_ptr != '\0'; src_ptr++, dest_ptr++, n--)
	{
		*dest_ptr = *src_ptr;
	}

	/* if n is greater than 0, continue counting down till 0,  */
	/* filling the remaining n chars of dest with \0 */
	for (; n > 0; dest_ptr++, n--)
	{
		*dest_ptr = '\0';
	}

	return (dest);
}
