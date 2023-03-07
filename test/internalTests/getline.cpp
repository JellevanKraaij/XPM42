#include <gtest/gtest.h>

#include <XPM42_int.h>

static const char getline_testfile[] =
	"CJNh7W73d55&%Du\n"
	"a#x@yNCUZ6ZRfAw\n"
	"\n"
	"a2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$ca2F58%Zz#HA$M6n$m4ygjPjF5KNaRK99ZJWvE@vjnFYB#ieMSR9CFu6*GPfvGnDJx$ha$UFvBFH%7M@yyba89ZPETNR%g3YrmKsGczT7w7W6&5!AQWGGb8mLr6dr#D$c";

TEST(utils, getline)
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
