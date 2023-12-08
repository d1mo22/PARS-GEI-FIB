#!/bin/bash

MIN=1
MAX=1267834

random_number=$(shuf -i $MIN-$MAX -n 1)

./Game Dummy DM7 Dummy Dummy -s $random_number -i default.cnf -o default.res 2> output.txt

