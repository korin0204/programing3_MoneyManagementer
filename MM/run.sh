gcc -Iinclude -c -o MMapp.o main.c
gcc -Iinclude -c -o read.o read.c
gcc -Iinclude -c -o write.o write.c
gcc -Iinclude -c -o utility.o utility.c
gcc -o MMapp MMapp.o read.o write.o calc.o utility.o
./MMapp