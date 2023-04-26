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
