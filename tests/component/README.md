## How to build
From project root folder:
```
$ mkdir build && cd build 
$ cmake -Dlightargparser_BUILD_CTESTS=on ..
```

## SimpleAppTest output examples

Example: Good arguments
```
$ ./SimpleAppTest -v --help -xyz DataKey1=DataValue1 DataKey2 --file=/temp/file1
Input arguments successfully parsed:
----------------------------------------
Config arguments:
    file: /temp/file1
    help: 
    v: 
    x: 
    y: 
    z: 
----------------------------------------
Data arguments:
    DataKey1: DataValue1
    DataKey2: 
----------------------------------------
Simple argument analysis:
    Version was requested by user!
----------------------------------------
```
Example: Bad argument
```
$ ./SimpleAppTest -v --help -xyz=bad_format DataKey1=DataValue1 DataKey2 --file=/temp/file1
Parsing input arguments failed!
----------------------------------------
Bad argument: -xyz=bad_format
----------------------------------------
```