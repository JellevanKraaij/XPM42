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

	for (uint32_t y = 0; y < header->height; y++)
	{
		for (uint32_t x = 0; x < header->width; x++)
		{
			char read_buffer[header->chars_per_pixel + 1];
			read_buffer[header->chars_per_pixel] = '\0';
			if (fread(&read_buffer, header->chars_per_pixel, 1, fp) != 1)
				return (free(*data), XPM_STREAM_ERROR_CODE(fp));
			xpm_error_t error;
			if ((error = xpm_lookup_color(header, read_buffer, &(*data)[y * header->width + x])))
				return (free(*data), error);
		}
		if ((getc(fp) != '\n' && y < header->height - 1) || (y == header->height - 1 && (fgetc(fp) != EOF || ferror(fp))))
			return (free(*data), XPM_STREAM_ERROR_CODE(fp));
	}
	return (XPM_SUCCESS);
}
