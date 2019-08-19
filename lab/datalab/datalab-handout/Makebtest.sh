#!/bin/sh
make clean && make btest
if [ $# < 1 ]; then
    echo "pls input a param"
else
    ./btest -f $1
fi
