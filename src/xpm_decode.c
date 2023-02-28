#include "XPM42.h"
#include "XPM42_int.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

xpm_error_t xpm_parse_header(xpm_header_t *header, FILE *file)
{
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;

	line_length = xpm_getline(&line, &line_cap, file);
	if (line_length < 0)
		return (XPM_READ_ERROR);
	if (strncmp(line, "!XPM42", line_cap))
		return (XPM_INV_FILE_FORMAT);
	if (sscanf(line, "%u %u %u %u", &header->width, &header->height, &header->color_cnt, &header->chars_per_pixel) != 4)
		return (XPM_INV_FILE_FORMAT);
	if (header->width == 0 || header->height == 0 || header->color_cnt == 0 || header->chars_per_pixel == 0)
		return (XPM_INV_FILE_FORMAT);
	return (XPM_SUCCESS);
}

static bool xpm_check_filename_type(const char *filename)
{
	char *dot_location = strrchr(filename, '.');

	if (!dot_location)
		return (false);

	if (strcmp(dot_location, ".xpm42"))
		return (false);
	return (true);
}

xpm_error_t xpm_decode32(uint32_t **data, uint32_t *width, uint32_t *height, const char *filename)
{
	if (!data || !width || !height || !filename || !strlen(filename))
		return XPM_INV_ARG;

	if (!xpm_check_filename_type(filename))
		return XPM_INV_FILE_TYPE;

	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return (XPM_OPEN_ERROR);
	
	xpm_header_t xpm_header;
	if (!xpm_parse_header(&xpm_header, file))
		return (XPM_INV_FILE_FORMAT);

	return XPM_SUCCESS;
}
