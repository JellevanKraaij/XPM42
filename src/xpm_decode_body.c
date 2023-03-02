#include "XPM42.h"
#include "XPM42_int.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static xpm_error_t xpm_lookup_color(const xpm_header_t *header, const char *name, uint32_t *value)
{
	for (uint32_t i = 0; i < header->color_cnt; i++)
	{
		if (!strncmp(name, header->color_names[i], header->chars_per_pixel))
		{
			*value = header->color_values[i];
			return (XPM_SUCCESS);
		}
	}
	return (XPM_INV_FILE_FORMAT);
}

xpm_error_t xpm_decode_body(uint32_t **data, const xpm_header_t *header, FILE *fp)
{
	if (!header || !data)
		return (XPM_INV_ARG);

	*data = malloc(header->width * header->height * sizeof(uint32_t));
	if (!*data)
		return (XPM_MEM_ERROR);

	for (uint32_t i = 0; i < header->height; i++)
	{
		for (uint32_t j = 0; j < header->width; j++)
		{
			char read_buffer[header->chars_per_pixel];
			if (fread(&read_buffer, header->chars_per_pixel, 1, fp) != header->chars_per_pixel)
				return (XPM_STREAM_ERROR_CODE(fp));
			xpm_error_t error;
			if ((error = xpm_lookup_color(header, read_buffer, &(*data)[i * header->width + j])))
				return (error);
		}
	}
	return (XPM_SUCCESS);
}