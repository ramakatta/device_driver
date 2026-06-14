 gcc -fprofile-arcs -ftest-coverage -o myprog myprog.c
./myprog
gcov myprog.c

