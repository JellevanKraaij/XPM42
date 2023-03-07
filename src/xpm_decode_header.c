#include "XPM42.h"
#include "XPM42_int.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static xpm_error_t xpm_decode_header_color(char *line, char **name, uint32_t *value, const xpm_header_t *header)
{
	char namebuf[header->chars_per_pixel + 1];
	namebuf[header->chars_per_pixel] = '\0';

	if (strlen(line) < header->chars_per_pixel)
		return (XPM_INV_FILE_FORMAT);
	strncpy(namebuf, line, header->chars_per_pixel);

	if (sscanf(line + header->chars_per_pixel, "%*1[ ]#%x", value) != 1)
		return (XPM_INV_FILE_FORMAT);
	*name = strdup(namebuf);
	if (!*name)
		return (XPM_MEM_ERROR);
	return (XPM_SUCCESS);
}

static xpm_error_t xpm_decode_header_colors(xpm_header_t *header, FILE *fp)
{
	header->color_names = calloc(header->color_cnt, sizeof(char *));
	header->color_values = calloc(header->color_cnt, sizeof(uint32_t));
	if (!header->color_names || !header->color_values)
		return (XPM_MEM_ERROR);

	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;

	for (unsigned int i = 0; i < header->color_cnt; i++)
	{
		line_length = xpm_getline(&line, &line_cap, fp);
		if (line_length < 0)
			return (free(line), XPM_STREAM_ERROR_CODE(fp));
		xpm_error_t error;	
		if ((error = xpm_decode_header_color(line, &header->color_names[i], &header->color_values[i], header)))
			return (free(line), error);
	}
	free(line);
	return (XPM_SUCCESS);
}

xpm_error_t xpm_decode_header(xpm_header_t *header, FILE *fp)
{
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;

	bzero(header, sizeof(xpm_header_t));

	line_length = xpm_getline(&line, &line_cap, fp);
	if (line_length < 0)
		return (free(line), XPM_STREAM_ERROR_CODE(fp));
	if (strncmp(line, "!XPM42\n", line_cap))
		return (free(line), XPM_INV_FILE_FORMAT);
	char color_mode;

	line_length = xpm_getline(&line, &line_cap, fp);
	if (line_length < 0)
		return (free(line), XPM_STREAM_ERROR_CODE(fp));
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
	xpm_error_t error;
	if ((error = xpm_decode_header_colors(header, fp)))
		return (xpm_header_destroy(header), error);
	return (XPM_SUCCESS);
}


void xpm_header_destroy(xpm_header_t *header)
{
	if (header->color_names)
	{
		for (unsigned int i = 0; i < header->color_cnt; i++)
			free(header->color_names[i]);
		free(header->color_names);
	}
	free(header->color_values);
	header->color_names = NULL;
	header->color_values = NULL;
}