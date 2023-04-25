#include <stdlib.h>

/**
 * _strcat - concatenates two strings
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
	src_ptr = src;

	/* Move the pointer up to the point where the null terminator is */
	while (*dest_ptr != '\0')
	{
		dest_ptr++;
	}

	/* Iterate through src_ptr, copying each value over to *dest_ptr */
	/* which now has its starting point where its null terminator is */
	while (*src_ptr != '\0')
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
	}

	/* Add a null terminator at the end of dest using dest_ptr */
	*dest_ptr = '\0';

	return (dest);
}

/**
 * _strncmp - compares two strings up to n characacters
 * @str1: first pointer to string
 * @str2: second pointer to string
 * @n: number of characters to compare
 * 
 * Return: negative, 0, or positive integer if s1 <, =, > s2 respectively
 * 		up to n characters.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0 && *str1 != '\0' && *str2!= '\0' && (*str1 == *str2))
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
	char *str_cpy;
	unsigned int i;
	unsigned int len = 0;

	if (str == NULL) /* return Null if string is NULL */
		return (NULL);
	while (str[len] != '\0')/* find length of string */
		len++;

	str_cpy = malloc((len + 1) * sizeof(char));

	if (str_cpy == NULL) /* return NULL on allocation fail */
		return (NULL);

	for (i = 0; i < len; i++) /* duplicate content from str into copy */
		str_cpy[i] = str[i];
	str_cpy[i] = '\0';

	return (str_cpy);
}

/**
 * _strlen - calculates the length of a string
 * @str: pointer to the string to be measured
 *
 * Return: the length of the string
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
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: num of chars to use
 *
 * Return: pointer to resulting destination string
 */
char *strncpy(char *dest, char *src, int n)
{
	char *dest_ptr;
	char *src_ptr;

	dest_ptr = dest;

	/* Iterate through src_ptr n times, copy each value to *dest_ptr */
	for (src_ptr = src; n > 0 && *src_ptr != '\0'; src_ptr++, n--)
	{
		*dest_ptr = *src_ptr;
	}

	/* if n > 0, continue counting down till 0, fill remaining */
	/* n chars of dest with \0 */
	for (; n > 0; dest_ptr++, n--)
	{
		*dest_ptr = '\0';
	}
	return (dest);
}

/* THE END */

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
