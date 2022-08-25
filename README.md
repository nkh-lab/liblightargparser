## Intro

To parse program arguments in next format:
```
-<Config Arg Key(one char short form)>=<Config Arg Value>
--<Config Arg Key(long form)>=<Config Arg Value>
<Data Arg Key>=<Data Arg Value>
``` 

## Examples

Example:
```
./my_prog -c1 -c2=true data1=data1_value1 data2 data3=data3_value3 --config3=config_value3
```