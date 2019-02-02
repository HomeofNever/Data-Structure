#! /bin/bash

./main.out input10.txt output10_replace.txt replace X O
./main.out input10.txt output10_dilation.txt dilation X
./main.out input10.txt output10_erosion.txt erosion X \.
./main.out output10_erosion.txt output10_opening.txt dilation X
./main.out output10_dilation.txt output10_closing.txt erosion X \.