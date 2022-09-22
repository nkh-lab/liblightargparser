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

#include <iostream>

#include "LightArgParser.h"

using namespace nkhlab::lightargparser;

int main(int argc, char const* argv[])
{
    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    if (lap.Parse(config_args, data_args, bad_arg))
    {
        std::cout << "Input arguments successfully parsed:\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Config arguments:\n";
        for (auto c : config_args)
        {
            std::cout << "    " << c.first << ": " << c.second << "\n";
        }
        std::cout << "----------------------------------------\n";
        std::cout << "Data arguments:\n";
        for (auto d : data_args)
        {
            std::cout << "    " << d.first << ": " << d.second << "\n";
        }
        std::cout << "----------------------------------------\n";
        std::cout << "Simple argument analysis:\n";

        if (LightArgParserHelper(config_args).AnyKeyExists({"v", "version"}))
        {
            std::cout << "    Version was requested by user!\n";
        }
        else
        {
            std::cout << "    Version wasn't requested by user.\n";
        }
        std::cout << "----------------------------------------\n";

        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "Parsing input arguments failed!\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Bad argument: " << bad_arg << "\n";
        std::cout << "----------------------------------------\n";

        return EXIT_FAILURE;
    }
}
