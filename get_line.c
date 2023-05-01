#include "shell.h"

/**
 * get_line - reads a line from a file descriptor and returns the number
 * of characters read (excluding the null terminator) or -1 if an error occurs
 * or end of file is reached.
 *
 * @line: double char pointer that will be allocated with the line read
 * from the file descriptor. The caller is responsible for freeing this memory.
 * @fd: the file descriptor to read from.
 *
 * Return: the number of characters read from the file descriptor
 * or -1 if an error occurs.
 */
int get_line(char **line, int fd)
{
	static char buff[BUFFER_SIZE];
	static int	buff_pos, buff_len;
	int			i, line_size = 0, line_capacity = BUFFER_SIZE;

	*line = malloc(line_capacity); /* allocate memory for a new line */
	if (*line == NULL)			   /* alloc fail */
		return (-1);
	while (1)
	{
		if (buff_pos == 0)
		{ /* if buffer empty/fully consumed, read again to refill buffer*/
			buff_len = read(fd, buff, BUFFER_SIZE);
			if (buff_len <= 0) /* end of file (eof) or error */
			{
				(*line)[line_size] = '\0'; /*null terminate line*/
				return (-1);
			}
			buff_len = strip_repeated_whitespace(buff, buff_len);
		}
		for (i = buff_pos; i < buff_len; i++) /*resume from last buff_pos*/
		{ /* buffer has content, so copy from buffer into line */
			if (line_size == line_capacity) /*realloc line if capacity reached*/
			{
				line_capacity *= LINE_FACTOR; /*increace capacity by a factor*/
				*line = realloc(*line, line_capacity);
				if (*line == NULL) /* alloc fail */
					return (-1);
			}
			(*line)[line_size] = buff[i];	/* copy buffer into line */
			if ((*line)[line_size] == '\n') /* if newline is found */
			{
				(*line)[line_size] = '\0';	/* null terminate line */
				buff_pos		   = i + 1; /* update buffer position */
				strip_lead_trail_whitespace(*line);
				return (line_size); /* return num of chars in line */
			}
			line_size++;
		}
		buff_pos = 0; /* buff fully read, reset it to start */
	}
}
