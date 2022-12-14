/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include "LightArgParser.h"

#include <gtest/gtest.h>

using namespace nkhlab::lightargparser;

template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N])
{
    return N;
}

TEST(LightArgParserTest, ParseShortFormConfigKey)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 1);
    EXPECT_NE(config_args.find("v"), config_args.end());
    EXPECT_EQ(data_args.size(), 0);
}

TEST(LightArgParserTest, ParseLongFormConfigKey)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 1);
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("version"));
    EXPECT_EQ(data_args.size(), 0);
}

TEST(LightArgParserTest, ParseComplexShortFormConfigKey)
{
    const char* argv[] = {"", "-xyz"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 3);
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("x"));
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("y"));
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("z"));
    EXPECT_EQ(data_args.size(), 0);
}

TEST(LightArgParserTest, ParseUnvalidShortFormConfigKey)
{
    const char* argv[] = {"", "--v"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_FALSE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 0);
    EXPECT_EQ(data_args.size(), 0);
    EXPECT_EQ(bad_arg, argv[1]);
}

TEST(LightArgParserTest, ParseUnvalidLongFormConfigKey)
{
    const char* argv[] = {"", "---version"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_FALSE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 0);
    EXPECT_EQ(data_args.size(), 0);
    EXPECT_EQ(bad_arg, argv[1]);
}

TEST(LightArgParserTest, ParseShortFormConfigKeyValue)
{
    const char* argv[] = {"", "-k=value"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 1);
    EXPECT_EQ(config_args["k"], "value");
    EXPECT_EQ(data_args.size(), 0);
}

TEST(LightArgParserTest, ParseUnvalidShortFormConfigKeyValue)
{
    const char* argv[] = {"", "-xyz=value"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_FALSE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 0);
    EXPECT_EQ(data_args.size(), 0);
    EXPECT_EQ(bad_arg, argv[1]);
}

TEST(LightArgParserTest, ParseLongFormConfigKeyValue)
{
    const char* argv[] = {"", "--key=value"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 1);
    EXPECT_EQ(config_args["key"], "value");
    EXPECT_EQ(data_args.size(), 0);
}

TEST(LightArgParserTest, ParseDataKeyValue)
{
    const char* argv[] = {"", "key=value"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 0);
    EXPECT_EQ(data_args.size(), 1);
    EXPECT_EQ(data_args["key"], "value");
}

TEST(LightArgParserTest, ParseMix)
{
    const char* argv[] = {
        "",
        "-c",
        "DataKey1=DataValue1",
        "--ConfigKey2=ConfigValue2",
        "DataKey2=DataValue2",
        "DataKey3=DataValue3",
        "-xyz"};
    int argc = arraySize(argv);

    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    EXPECT_TRUE(lap.Parse(config_args, data_args, bad_arg));
    EXPECT_EQ(config_args.size(), 5);
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("c"));
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("x"));
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("y"));
    EXPECT_TRUE(LightArgParserHelper(config_args).KeyExists("z"));
    EXPECT_EQ(config_args["ConfigKey2"], "ConfigValue2");
    EXPECT_EQ(data_args.size(), 3);
    EXPECT_EQ(data_args["DataKey1"], "DataValue1");
    EXPECT_EQ(data_args["DataKey2"], "DataValue2");
    EXPECT_EQ(data_args["DataKey3"], "DataValue3");
}