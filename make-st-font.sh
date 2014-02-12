#!/bin/sh
# Edit the stfont.xbm, then run this with output to a .h or .c -> there's your font.
gcc -O2 -W -std=gnu99 -o genfont-st7565 genfont-st7565.c
./genfont-st7565
