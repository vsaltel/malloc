#!/bin/bash

gcc ./tests/test0.c -o test0
gcc ./tests/test1.c -o test1
gcc ./tests/test2.c -o test2
gcc ./tests/test3.c -o test3
gcc ./tests/test4.c -o test4
gcc ./tests/test5.c -o test5
gcc ./tests/test6.c -o test6 -L. -lft_malloc
gcc ./tests/test7.c -o test7 -L. -lft_malloc
