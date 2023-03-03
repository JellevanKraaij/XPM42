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
		char *tmp = realloc(*line, sizeof(chunk));
		if (!tmp)
			return (-1);
		*line = tmp;
		*line_size = sizeof(chunk);
	}
	*line[0] = '\0';

	while (fgets(chunk, sizeof(chunk), file))
	{
		if (*line_size - strlen(*line) < sizeof(chunk))
		{
			char *tmp = realloc(*line, *line_size * 2);
			if (!tmp)
				return (-1);
			*line = tmp;
			*line_size *= 2;
		}
		strcat(*line, chunk);

		line_length = strlen(*line);
		if ((*line)[line_length - 1] == '\n' || ((*line)[line_length - 1] == '\r' && (*line)[line_length - 2] == '\n'))
			return (line_length);
	}
	if (line_length > 0)
		return (line_length);
	return (-1);
}
