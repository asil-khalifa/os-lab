#!/bin/bash
var1="Apple"
myfun(){
local var2="Khalifa"
echo "Inside func $var2 $var1"
}
myfun
echo "OUtside $var1"
