#include <gtest/gtest.h>

#include <XPM42_int.h>

static const char parse_header_testfile[] =
	"!XPM42\n"
	"16 16 3 1 c\n"
	"a #00000000\n"
	"b #FFFFFFFF\n"
	"c #FF00FF00\n";

TEST(header, valid)
{
	xpm_header_t	header;
	xpm_error_t		res;

	FILE *fp = fmemopen((void *)parse_header_testfile, strlen(parse_header_testfile), "r");
	ASSERT_NE(fp, nullptr);

	res = xpm_decode_header(&header, fp);
	ASSERT_EQ(res, XPM_SUCCESS);

	EXPECT_EQ(header.width, 16);
	EXPECT_EQ(header.height, 16);
	EXPECT_EQ(header.color_mode, XPM_MODE_NORMAL);
	
	ASSERT_EQ(header.chars_per_pixel, 1);
	ASSERT_EQ(header.color_cnt, 3);

	EXPECT_STREQ(header.color_names[0], "a");
	EXPECT_EQ(header.color_values[0], 0x00000000);

	EXPECT_STREQ(header.color_names[1], "b");
	EXPECT_EQ(header.color_values[1], 0xFFFFFFFF);

	EXPECT_STREQ(header.color_names[2], "c");
	EXPECT_EQ(header.color_values[2], 0xFF00FF00);

	for (unsigned int i = 0; i < header.color_cnt; i++) {
		free(header.color_names[i]);
	}

	free(header.color_names);
	free(header.color_values);
}
