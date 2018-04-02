#!/usr/bin/env bash
# https://stackoverflow.com/a/7110046

# compile -w to suppress warnings
gcc  runtest.c ./test/*.c ./src/test/*.c ./src/admin/*.c ./src/data/*.c ./src/filter/*.c -o ./out/test.out

# run
./out/test.out
