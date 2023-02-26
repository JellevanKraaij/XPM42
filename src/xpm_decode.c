#include "XPM42.h"
#include <string.h>
#include <stdbool.h>

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
	
	return XPM_SUCCESS;
}
