#!/usr/bin/env bash
# https://stackoverflow.com/a/7110046
# compile
gcc  main.c ./src/test/*.c ./src/admin/*.c ./src/data/*.c ./src/filter/*.c ./src/node/*.c ./src/list/*.c ./src/db/*.c ./src/menu/*.c -o ./out/main.out

# run
./out/main.out
