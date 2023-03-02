#include "XPM42.h"
#include "XPM42_int.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static xpm_error_t xpm_parse_header_color(char *line, char **name, uint32_t *value, const xpm_header_t *header)
{
	char format[10];
	snprintf(format, sizeof(format), "%%%ds #%%x", header->chars_per_pixel);
	char namebuf[header->chars_per_pixel + 1];
	if (sscanf(line, format, namebuf, value) != 2)
		return (XPM_INV_FILE_FORMAT);
	*name = strdup(namebuf);
	if (!*name)
		return (XPM_MEM_ERROR);
	return (XPM_SUCCESS);
}

static xpm_error_t xpm_parse_header_colors(xpm_header_t *header, FILE *fp)
{
	header->color_names = NULL;
	header->color_values = NULL;
	header->color_names = calloc(header->color_cnt, sizeof(char *));
	header->color_values = calloc(header->color_cnt, sizeof(uint32_t));
	if (!header->color_names || !header->color_values)
		return (free(header->color_names), free(header->color_values), XPM_MEM_ERROR);

	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;

	for (unsigned int i = 0; i < header->color_cnt; i++)
	{
		line_length = xpm_getline(&line, &line_cap, fp);
		if (line_length < 0)
			return (free(line), XPM_READ_ERROR);
		xpm_error_t error;	
		if ((error = xpm_parse_header_color(line, &header->color_names[i], &header->color_values[i], header)))
			return (free(line), error);
	}
	free(line);
	return (XPM_SUCCESS);
}

xpm_error_t xpm_parse_header(xpm_header_t *header, FILE *fp)
{
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;

	line_length = xpm_getline(&line, &line_cap, fp);
	if (line_length < 0)
		return (free(line), XPM_READ_ERROR);
	if (strncmp(line, "!XPM42\n", line_cap))
		return (free(line), XPM_INV_FILE_FORMAT);
	char color_mode;

	line_length = xpm_getline(&line, &line_cap, fp);
	if (line_length < 0)
		return (free(line), XPM_READ_ERROR);
	if ((sscanf(line, "%u %u %u %u %c", &header->width, &header->height, &header->color_cnt, &header->chars_per_pixel, &color_mode)) != 5)
		return (free(line), XPM_INV_FILE_FORMAT);
	free(line);
	if (header->width == 0 || header->height == 0 || header->color_cnt == 0 || header->chars_per_pixel == 0)
		return (XPM_INV_FILE_FORMAT);
	if (tolower(color_mode) == 'c')
		header->color_mode = XPM_MODE_NORMAL;
	else if (tolower(color_mode) == 'm')
		header->color_mode = XPM_MODE_MONOCHROME;
	else
		return (XPM_INV_FILE_FORMAT);
	
	return (xpm_parse_header_colors(header, fp));
}