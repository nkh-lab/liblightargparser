#include "LightArgParser.h"

#include <gtest/gtest.h>

using namespace nlab;

template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N])
{
    return N;
}

TEST(LightArgParserTest, ParseOneShortFormConfigKey)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 1);
    EXPECT_NE(config.find("v"), config.end());
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseOneLongFormConfigKey)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 1);
    EXPECT_NE(config.find("version"), config.end());
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseUnOneShortFormConfigKey)
{
    const char* argv[] = {"", "--v"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_FALSE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseUnOneLongFormConfigKey)
{
    const char* argv[] = {"", "-version"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_FALSE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseUnOneShortFormConfigKey1)
{
    const char* argv[] = {"", "---v"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_FALSE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseUnOneLongFormConfigKey1)
{
    const char* argv[] = {"", "---version"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_FALSE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseOneShortFormConfigKeyValue)
{
    const char* argv[] = {"", "-f=~/temp/file1"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 1);
    EXPECT_EQ(config["f"], "~/temp/file1");
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseOneLongFormConfigKeyValue)
{
    const char* argv[] = {"", "--file=~/temp/file1"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 1);
    EXPECT_EQ(config["file"], "~/temp/file1");
    EXPECT_EQ(data.size(), 0);
}

TEST(LightArgParserTest, ParseOneDataKeyValue)
{
    const char* argv[] = {"", "DataKey1=DataValue1"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data["DataKey1"], "DataValue1");
}

TEST(LightArgParserTest, ParseMix)
{
    const char* argv[] = {
        "",
        "-v",
        "DataKey1=DataValue1",
        "--file=~/temp/file1",
        "DataKey2=DataValue2",
        "DataKey3=DataValue3"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_TRUE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 2);
    EXPECT_NE(config.find("v"), config.end());
    EXPECT_EQ(config["file"], "~/temp/file1");
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data["DataKey1"], "DataValue1");
    EXPECT_EQ(data["DataKey2"], "DataValue2");
    EXPECT_EQ(data["DataKey3"], "DataValue3");
}

TEST(LightArgParserTest, ParseUnMix)
{
    const char* argv[] = {
        "",
        "-v",
        "DataKey1=DataValue1",
        "--file=~/temp/file1",
        "DataKey2=DataValue2",
        "DataKey3=DataValue3",
        "---help"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    std::map<ArgKey_t, ArgVal_t> config, data;

    EXPECT_FALSE(lap.Parse(config, data));
    EXPECT_EQ(config.size(), 0);
    EXPECT_EQ(data.size(), 0);
}