#!/bin/sh

SRC="main.c init.c input.c menu.c draw.c user_input.c"

ld -r -b binary textures/alph.png -o alph.o
ld -r -b binary textures/color_picker.png -o color_picker.o

#gcc -g $SRC alph.o color_picker.o -lSDL3 -lSDL3_image -o pixedit

#gcc -c src/*.c

gcc -g ./src/*.c ./*.o -o pixedit -lSDL3 -lSDL3_image

rm *.o

