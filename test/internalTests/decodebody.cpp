#include <gtest/gtest.h>

#include <XPM42_int.h>

#include "decodebodyfixture.hpp"


TEST_P(decodeBody, basic)
{
	xpm_error_t		res;
	uint32_t		*data = NULL;

	res = xpm_decode_body(&data, &GetParam().header, fp);
	if (GetParam().isValid) {
		ASSERT_EQ(res, XPM_SUCCESS);
		ASSERT_NE(data, nullptr);
		EXPECT_EQ(memcmp(data, GetParam().expectedData, GetParam().header.width * GetParam().header.height * sizeof(uint32_t)), 0);
		EXPECT_TRUE(feof(fp));
		free(data);
	} else {
		EXPECT_EQ(res, XPM_INV_FILE_FORMAT);
	}
}

static const xpm_header_t singleChar_header = {
	.width = 2,
	.height = 3,
	.color_cnt = 3,
	.chars_per_pixel = 1,
	.color_mode = XPM_MODE_NORMAL,
	.color_names = (char *[]){(char *)"a", (char *)"b", (char *)"c"},
	.color_values = (uint32_t[]){0x00000000, 0xFFFFFFFF, 0xFF00FF00}
};

static const xpm_header_t multiChar_header = {
	.width = 2,
	.height = 3,
	.color_cnt = 3,
	.chars_per_pixel = 3,
	.color_mode = XPM_MODE_NORMAL,
	.color_names = (char *[]){(char *)"abc", (char *)"abb", (char *)"aaa"},
	.color_values = (uint32_t[]){0x00000000, 0xFFFFFFFF, 0xFF00FF00}
};


static const DecodeBodyParams decodeBodyParams[] =
{
	// Valid tests
	{
		.fileContent = (char *)"aa\nbb\naa\n",
		.header = singleChar_header,
		.isValid = true, 
		.expectedData = (uint32_t[]){0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000},
		.name = "singleChar1"
	},
	{
		.fileContent = (char *)"aa\nbb\naa",
		.header = singleChar_header,
		.isValid = true, 
		.expectedData = (uint32_t[]){0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000},
		.name = "singleChar1NoNewline"
	},
	{
		.fileContent = (char *)"ab\ncb\nca\n",
		.header = singleChar_header,
		.isValid = true,
		.expectedData = (uint32_t[]){0x00000000, 0xFFFFFFFF, 0xFF00FF00, 0xFFFFFFFF, 0xFF00FF00, 0x00000000},
		.name = "singleChar2"
	},
	{
		.fileContent = (char *)"abcabb\naaaabb\naaaabc",
		.header = multiChar_header,
		.isValid = true,
		.expectedData = (uint32_t[]){0x00000000, 0xFFFFFFFF, 0xFF00FF00, 0xFFFFFFFF, 0xFF00FF00, 0x00000000},
		.name = "multiChar"
	},
	
	// Invalid tests
	{
		.fileContent = (char *)"aa\nb\naa\n",
		.header = singleChar_header,
		.isValid = false,
		.expectedData = nullptr,
		.name = "singleChar1"
	},
	{
		.fileContent = (char *)"aa\nbb\naa\na",
		.header = singleChar_header,
		.isValid = false,
		.expectedData = nullptr,
		.name = "singleChar2"
	},
	{
		.fileContent = (char *)"aa\nbb\nda\n",
		.header = singleChar_header,
		.isValid = false,
		.expectedData = nullptr,
		.name = "singleChar3"
	},

	{
		.fileContent = (char *)"abcabb\naaabb\naaaabc\n",
		.header = multiChar_header,
		.isValid = false,
		.expectedData = nullptr,
		.name = "multiChar1"
	},
	{
		.fileContent = (char *)"abcabb\nacaabb\naaaabc",
		.header = multiChar_header,
		.isValid = false,
		.expectedData = nullptr,
		.name = "multiChar2"
	}
};


INSTANTIATE_TEST_SUITE_P(
	P,
	decodeBody,
	::testing::ValuesIn(decodeBodyParams)
);