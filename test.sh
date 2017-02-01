#!/bin/bash

rm pi
make
./pi >> results.txt
rm pi2
make pi2
./pi2 >> results.txt
rm pi3
make pi3
./pi3 >> results.txt
rm pi4
make pi4
./pi4 >> results.txt
