#!/bin/bash

MIN=1
MAX=1267834

random_number=$(shuf -i $MIN-$MAX -n 1)

./Game DM7 Dummy Dummy Dummy -s 1222933 -i default.cnf -o default.res 2> output.txt

