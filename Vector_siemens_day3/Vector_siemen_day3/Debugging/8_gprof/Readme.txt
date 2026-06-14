 gcc -pg your_code.c -o your_program
./your_program
It will produce a file called gmon.out in the current directory when it finishes.
gprof your_program gmon.out > analysis.txt

