## Intro

Lightweight static library for parsing program input arguments in `<Key>=<Value>` format. 

If `<Key>` starts with "-" (one minus character) or "--" (two minus characters), it is called **a configuration argument**, otherwise it is called **a data argument**.

Configuration arguments examples:
```
-v
--help
-xyz // equals -x -y -z
--file=/temp/file1
```
Data arguments examples:
```
DataKey1 // with omitted value
DataKey2=DataValue2
```
Application run example:
```
$ ./my-app -v --help -xyz DataKey1 DataKey2=DataValue2 --file=/temp/file1
```
## Build Status
[![CI](https://github.com/nkh-lab/liblightargparser/actions/workflows/ci.yml/badge.svg)](https://github.com/nkh-lab/liblightargparser/actions/workflows/ci.yml)

## How to use
This is a cmake based project, so add it to your build process, link your target to the `lightargparser` library, and include the `LightArgParser.h` header in your source code.

API usage example:
```
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
        if (!config_args.empty())
        {
            if (LightArgParserHelper(config_args).AnyKeyExists({"v", "version"}))
                std::cout << "v1.0.0\n";
            std::cout << "Configuration arguments <key>: <value>:\n";
            for (auto c : config_args) std::cout << "    " << c.first << ": " << c.second << "\n";
        }
        else
            std::cout << "No configuration arguments provided!\n";

        if (!data_args.empty())
        {
            std::cout << "Data arguments <key>: <value>:\n";
            for (auto d : data_args) std::cout << "    " << d.first << ": " << d.second << "\n";
        }
        else
            std::cout << "No data arguments provided!\n";
    }
    else
        std::cout << "Bad argument: " << bad_arg << "\n";

    // ...
}
```
And its execution:
```
./myapp -r=RPSH_1 -t=100 -v data1=100 data2
v1.0.0
Configuration arguments <key>: <value>:
    r: RPSH_1
    t: 100
    v:
Data arguments <key>: <value>:
    data1: 100
    data2:
```

For more details, refer to [tests/component](tests/component) as a real example of `lightargparser` library usage.
