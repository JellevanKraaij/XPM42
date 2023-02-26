#include <XPM42.h>
#include <gtest/gtest.h>

TEST(XPM42, invalidParams) {
	uint32_t	*data;
	uint32_t	width;
	uint32_t	height;

	xpm_error_t res = xpm_decode32(NULL, NULL, NULL, NULL);
	EXPECT_EQ(res, XPM_INV_ARG);

	res = xpm_decode32(NULL, NULL, NULL, "test.xpm");
	EXPECT_EQ(res, XPM_INV_ARG);

	res = xpm_decode32(&data, &width, &height, "");
	EXPECT_EQ(res, XPM_INV_ARG);
}

TEST(XPM42, invalidFile) {
	uint32_t	*data;
	uint32_t	width;
	uint32_t	height;
	xpm_error_t res;


	data = NULL;
	res = xpm_decode32(&data, &width, &height, "test.xpm4");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);

	data = NULL;
	res = xpm_decode32(&data, &width, &height, "test.");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);

	data = NULL;
	res = xpm_decode32(&data, &width, &height, "test");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);
}
