#include <XPM42.h>
#include <XPM42_int.h>
#include <gtest/gtest.h>

TEST(parameters, invalid) {

	xpm_error_t res = xpm_decode(NULL, NULL, NULL, NULL);
	EXPECT_EQ(res, XPM_INV_ARG);

	res = xpm_decode(NULL, NULL, NULL, "test.xpm");
	EXPECT_EQ(res, XPM_INV_ARG);
}

TEST(file, invalid) {
	uint32_t	*data;
	uint32_t	width;
	uint32_t	height;
	xpm_error_t res;

	data = NULL;
	res = xpm_decode(&data, &width, &height, "");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);

	data = NULL;
	res = xpm_decode(&data, &width, &height, "test.xpm4");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);

	data = NULL;
	res = xpm_decode(&data, &width, &height, "test.");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);

	data = NULL;
	res = xpm_decode(&data, &width, &height, "test");
	EXPECT_EQ(res, XPM_INV_FILE_TYPE);
	free(data);

	data = NULL;
	res = xpm_decode(&data, &width, &height, "nonexisting.xpm42");
	EXPECT_EQ(res, XPM_OPEN_ERROR);
	free(data);
}

TEST(file, valid) {
	uint32_t	*data;
	uint32_t	width;
	uint32_t	height;
	xpm_error_t res;

	data = NULL;
	res = xpm_decode(&data, &width, &height, "assets/simple.xpm42");
	EXPECT_EQ(res, XPM_SUCCESS);
	EXPECT_NE(data, nullptr);
	free(data);
}

TEST(largeFile, valid) {
	uint32_t	*data;
	uint32_t	width;
	uint32_t	height;
	xpm_error_t res;

	data = NULL;
	res = xpm_decode(&data, &width, &height, "assets/large.xpm42");
	EXPECT_EQ(res, XPM_SUCCESS);
	EXPECT_NE(data, nullptr);
	free(data);
}
