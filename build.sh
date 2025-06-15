#!/bin/sh

SRC="main.c init.c input.c menu.c draw.c"

gcc -g $SRC -lSDL2 -o pixedit
