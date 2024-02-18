#include "shell.h"



/**
 *  * _strlen - Returns the length of a string.
 *   * @s: The string whose length to check.
 *    *
 *     * Return: Integer length of the string.
 *      */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 *  * _strcmp - Performs lexicographic comparison of two strings.
 *   * @s1: The first string.
 *    * @s2: The second string.
 *     *
 *      * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 *       */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}


char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

