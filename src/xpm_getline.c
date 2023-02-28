#include "XPM42_int.h"

#include <string.h>
#include <stdlib.h>

ssize_t xpm_getline(char **line, size_t *line_size, FILE *file)
{
	static char chunk[128];
	size_t line_length = 0;

	if (!line || !line_size || !file)
		return (-1);

	if (!*line || *line_size < sizeof(chunk))
	{
		*line = reallocf(*line, sizeof(chunk));
		if (!*line)
			return (-1);
		*line_size = sizeof(chunk);
	}
	*line[0] = '\0';

	while (fgets(chunk, sizeof(chunk), file))
	{
		if (*line_size - strlen(*line) < sizeof(chunk))
		{
			*line = reallocf(*line, *line_size * 2);
			if (!*line)
				return (*line_size = 0, -1);
			*line_size *= 2;
		}
		strcat(*line, chunk);

		line_length = strlen(*line);
		if ((*line)[line_length - 1] == '\n')
			return (line_length);
	}
	if (line_length > 0)
		return (line_length);
	return (-1);
}
