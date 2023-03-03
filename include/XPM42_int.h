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

#define XPM_STREAM_ERROR_CODE(fp) (ferror(fp) ? XPM_READ_ERROR : XPM_INV_FILE_FORMAT)

ssize_t xpm_getline(char **lineptr, size_t *n, FILE *stream);
xpm_error_t xpm_decode_header(xpm_header_t *header, FILE *fp);
xpm_error_t xpm_decode_body(uint32_t **data, const xpm_header_t *header, FILE *fp);

void xpm_header_destroy(xpm_header_t *header);

#ifdef __cplusplus
}
#endif

#endif

