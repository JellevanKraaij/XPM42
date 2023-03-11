#include "XPM42.h"
#include "XPM42_int.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static xpm_error_t xpm_lookup_color(const xpm_header_t *header, const char *str, uint32_t *value)
{
	for (uint32_t i = 0; i < header->color_cnt; i++)
	{
		if (!strncmp(str, header->color_names[i], header->chars_per_pixel))
		{
			*value = header->color_values[i];
			return (XPM_SUCCESS);
		}
	}
	return (XPM_INV_FILE_FORMAT);
}

xpm_error_t xpm_decode_body(uint32_t **data, const xpm_header_t *header, FILE *fp)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t len = 0;


	if (!header || !data)
		return (XPM_INV_ARG);

	*data = malloc(header->width * header->height * sizeof(uint32_t));
	if (!*data)
		return (XPM_MEM_ERROR);

	for (uint32_t y = 0; y < header->height; y++)
	{
		len = xpm_getline(&line, &line_size, fp);
		if (len < 0)
			return (free(line), free(*data), XPM_STREAM_ERROR_CODE(fp));
		if (line[len - 1] == '\n')
			len--;
		if (line[len - 1] == '\r')
			len--;
		if (len != header->width * header->chars_per_pixel)
			return (free(line), free(*data), XPM_INV_FILE_FORMAT);
		for (uint32_t x = 0; x < header->width; x++)
		{
			char *str = line + x * header->chars_per_pixel;
			uint32_t value = 0;
			xpm_error_t err = xpm_lookup_color(header, str, &value);
			if (err != XPM_SUCCESS)
				return (free(line), free(*data), err);
			(*data)[y * header->width + x] = value;
		}
	}
	free(line);
	if (fgetc(fp) != EOF)
		return (free(*data), XPM_STREAM_ERROR_CODE(fp));
	return (XPM_SUCCESS);
}
