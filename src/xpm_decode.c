#include "XPM42.h"
#include "XPM42_int.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static bool xpm_check_filename_type(const char *filename)
{
	char *dot_location = strrchr(filename, '.');

	if (!dot_location)
		return (false);

	if (strcmp(dot_location, ".xpm42"))
		return (false);
	return (true);
}

xpm_error_t xpm_decode(uint32_t **data, uint32_t *width, uint32_t *height, const char *file)
{
	if (!data || !width || !height || !file)
		return XPM_INV_ARG;

	if (!xpm_check_filename_type(file))
		return XPM_INV_FILE_TYPE;

	FILE *fp = fopen(file, "r");
	if (fp == NULL)
		return (XPM_OPEN_ERROR);
	
	xpm_header_t header;
	xpm_error_t error;
	if ((error = xpm_decode_header(&header, fp)))
		return (fclose(fp), error);

	uint32_t *decoded_data;
	if ((error = xpm_decode_body(&decoded_data, &header, fp)))
		return (fclose(fp), error);

	xpm_header_destroy(&header);
	fclose(fp);

	*width = header.width;
	*height = header.height;
	*data = decoded_data;

	return (XPM_SUCCESS);
}
