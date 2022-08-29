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
[![CI](https://github.com/nkh-lab/light-arg-parser/actions/workflows/ci.yml/badge.svg)](https://github.com/nkh-lab/light-arg-parser/actions/workflows/ci.yml)

## How to use
This is a cmake based project, so add it to your build process, link your target to the `lightargparser` library, and include the `LightArgParser.h` header in your source code.

API usage example:
```
#include "LightArgParser.h"

using namespace nlab;

int main(int argc, char const* argv[])
{
    LightArgParser lap(argc, argv);

    Args_t config_args, data_args;
    std::string bad_arg;

    if (lap.Parse(config_args, data_args, bad_arg))
    {
        if (LightArgParserHelper::AnyKeyExists(config_args, {"v", "version"}))
            std::cout << "v1.0.0\n";

        for (auto d : data_args)
            std::cout << d.first << ": " << d.second << "\n";
    }
    else
        std::cout << "Bad argument: " << bad_arg << "\n";

    ...    
}
```
For more details, see [tests/component](tests/component) as a real example of `lightargparser` library usage.
