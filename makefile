main: main.c tad.c
        gcc -o main main.c tad.c -I.
clean:
        rm -rf *.o
        rm -rf main
run:
        ./main