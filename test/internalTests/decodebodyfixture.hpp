#pragma once

#include <gtest/gtest.h>
#include <stdio.h>


#include <XPM42.h>

struct DecodeBodyParams {
	const char 		*name;
	char			*fileContent;
	bool 			isValid;
	uint32_t 		*expectedData;
	xpm_header_t	header;
};

void PrintTo(const DecodeBodyParams &params, std::ostream *os) {
	*os << (params.isValid ? "valid" : "invalid") << "/" << params.name;
}

class decodeBody : public testing::TestWithParam<DecodeBodyParams> {
public:
	FILE *fp;
	xpm_header_t header;


	inline void SetUp() override {
		fp = fmemopen((void *)GetParam().fileContent, strlen(GetParam().fileContent), "r");
		ASSERT_NE(fp, nullptr);
	}

	inline void TearDown() override {
		ASSERT_FALSE(ferror(fp));
		fclose(fp);
	}
};
