#ifndef XPM42_H
# define XPM42_H

#include <stdint.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef enum {
	XPM_SUCCESS = 0,
	XPM_INV_ARG,
	XPM_INV_FILE_TYPE,
	XPM_OPEN_ERROR,
	XPM_READ_ERROR,
	XPM_MEM_ERROR,
	XPM_INV_FILE_FORMAT,
} xpm_error_t;

xpm_error_t xpm_decode(uint32_t **data, uint32_t *width, uint32_t *height, const char *file);

# ifdef __cplusplus
}
# endif

#endif
