#ifndef XPM42_INT_H
#define XPM42_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "XPM42.h"

#include <stddef.h>
#include <stdio.h>

typedef enum {
	XPM_MODE_NORMAL,
	XPM_MODE_MONOCHROME,
} xpm_color_mode_t;

typedef struct {
	unsigned int	width;
	unsigned int	height;
	unsigned int	color_cnt;
	unsigned int	chars_per_pixel;
	xpm_color_mode_t color_mode;

	char			**color_names;
	uint32_t		*color_values;

} xpm_header_t;

ssize_t xpm_getline(char **lineptr, size_t *n, FILE *stream);
xpm_error_t xpm_parse_header(xpm_header_t *header, FILE *fp);

#ifdef __cplusplus
}
#endif

#endif

