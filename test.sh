#!/bin/bash

gcc ./tests/test0.c -o test0
gcc ./tests/test1.c -o test1
gcc ./tests/test2.c -o test2
gcc ./tests/test3.c -o test3
gcc ./tests/test3_bis.c -o test3_bis
gcc ./tests/test4.c -o test4
gcc ./tests/test5.c -o test5 -L. -lft_malloc
gcc ./tests/mytest.c -o mytest -L. -lft_malloc
