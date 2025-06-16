#!/bin/sh

SRC="main.c init.c input.c menu.c draw.c user_input.c"

gcc -g $SRC -lSDL3 -lSDL3_image -o pixedit
