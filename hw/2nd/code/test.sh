#! /bin/bash

./main.out input4.txt output4_replace.txt replace X O
./main.out input4.txt output4_dilation.txt dilation X
./main.out input4.txt output4_erosion.txt erosion X \.
./main.out output4_erosion.txt output4_opening.txt dilation X
./main.out output4_dilation.txt output4_closing.txt erosion X \.