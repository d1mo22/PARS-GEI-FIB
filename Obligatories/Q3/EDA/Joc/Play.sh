#!/bin/bash

MIN=1
MAX=1267834

random_number=$(shuf -i $MIN-$MAX -n 1)

./Game DM6 Dummy Dummy Dummy -s 941294 -i default.cnf -o default.res 2> output.txt

