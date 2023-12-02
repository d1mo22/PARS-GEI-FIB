#!/bin/bash

MIN=1
MAX=1267834

random_number=$(shuf -i $MIN-$MAX -n 1)

./Game DM4 DM3 DM3 DM3 -s $random_number -i default.cnf -o default.res 2> output.txt

