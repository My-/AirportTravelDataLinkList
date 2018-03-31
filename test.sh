#!/usr/bin/env bash
# https://stackoverflow.com/a/7110046

# compile
gcc -w test.c ./test/*.c ./src/*.c -o ./out/test.out

# run
./out/test.out
