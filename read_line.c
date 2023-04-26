#include "shell.h"
/**
 * read_line - reads an arbitrary line of input from a file descriptor
 * @fd: the file descriptor to read from
 * @input: the buffer to store the input in
 *
 * Return: the number of bytes read, or -1 if an error occurred
 */
int read_line(int fd, char *input)
{
	int		i = 0, j = 0, eof = 0;
	char	buffer[BUFFER_SIZE];
	ssize_t num_chars_read;

	/* Loop until a newline character is read or end of file is reached */
	while (!eof)
	{
		/* Read in a block of characters */
		num_chars_read = read(fd, buffer, BUFFER_SIZE);
		if (num_chars_read == -1)
		{
			return (-1);
		}
		else if (num_chars_read == 0)
		{
			eof = 1;
		}

		/* Copy characters into input string until newline or end of */
		/* buffer isreached */
		for (j = 0; j < num_chars_read; j++)
		{
			if (buffer[j] != '\n' && i != BUFFER_SIZE - 1)
			{
				input[i] = buffer[j];
				i++;
			}
			else
			{
				/*null terminate the string*/
				input[i] = '\0';
				return (i); /*return the number of chars copied/read*/
			}
		}
	}
	return (-1);
}
