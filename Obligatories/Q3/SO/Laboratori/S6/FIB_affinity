#!/bin/bash

if [ "$#" -ne 1 ]
then
	echo "usage $0 PU_id" 
	echo "PU_id: Processor unit identifier"
	exit
fi

echo $1

/usr/bin/time taskset -c $1 ./fib 45&
