#include <XPM42.h>
#include <XPM42_int.h>
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

	data = NULL;
	res = xpm_decode32(&data, &width, &height, "nonexisting.xpm42");
	EXPECT_EQ(res, XPM_OPEN_ERROR);
	free(data);
}

static const char getline_testfile[] =
"CJNh7W73d55&%Du\n"
"a#x@yNCUZ6ZRfAw\n"
"\n"
"a2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$ca2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$c"
;


TEST(XPM42_int, getline)
{
	ssize_t		len;

	len = xpm_getline(NULL, NULL, NULL);
	EXPECT_EQ(len, -1);


	FILE *fp = fmemopen((void *)getline_testfile, strlen(getline_testfile), "r");
	ASSERT_NE(fp, nullptr);

	char *line = NULL;
	size_t n = 0;

	len = xpm_getline(&line, &n, fp);
	EXPECT_EQ(len, 16);
	EXPECT_GT(n, 16);
	EXPECT_STREQ(line, "CJNh7W73d55&%Du\n");

	len = xpm_getline(&line, &n, fp);
	EXPECT_EQ(len, 16);
	EXPECT_GT(n, 16);
	EXPECT_STREQ(line, "a#x@yNCUZ6ZRfAw\n");

	len = xpm_getline(&line, &n, fp);
	EXPECT_EQ(len, 1);
	EXPECT_GT(n, 1);
	EXPECT_STREQ(line, "\n");

	len = xpm_getline(&line, &n, fp);
	EXPECT_EQ(len, 256);
	EXPECT_GT(n, 256);
	EXPECT_STREQ(line, "a2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$ca2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$c");

	len = xpm_getline(&line, &n, fp);
	EXPECT_EQ(len, -1);

	free(line);

	EXPECT_FALSE(ferror(fp));
	EXPECT_TRUE(feof(fp));

	fclose(fp);
}

//TODO: build a test for xpm_parse_header

// TEST(XPM42_int, parse_header)
// {
// 	xpm_header_t	header;
// 	xpm_error_t	res;

// 	res = xpm_parse_header(NULL, NULL);
// 	EXPECT_EQ(res, XPM_INV_ARG);

// 	res = xpm_parse_header(&header, NULL);
// 	EXPECT_EQ(res, XPM_INV_ARG);

// 	FILE *fp = fmemopen(NULL, 512, "w+");

// 	ASSERT_NE(fp, nullptr);

// 	fputs("/* XPM */\n", fp);
// 	fputs("static char * test_xpm[] = {\n", fp);
// 	fputs("\"16 16 3 1\",\n", fp);
// 	fputs("\"a c #000000\",\n", fp);
// 	fputs("\"b c #FFFFFF\",\n", fp);
// 	fputs("\"c c #FF0000\",\n", fp);
// }