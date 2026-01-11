#!/bin/bash

#aquest script s'executa en linux fent: bash scriptKisSAT.sh

start_measuring_time() {
  read start < <(date +'%s')
}

stop_measuring_time() {
  read end < <(date +'%s')
}

show_elapsed_time() {
  echo "$((end-start)) s"
}

#for f in vars-100*.cnf
for f in random3SAT/vars*.cnf
do
    echo
    echo "------------------"
    echo $f
    echo "KisSAT:"
    start_measuring_time
    kissat -v $f > outKisSAT
    stop_measuring_time
    egrep -o "UNSATISFIABLE|SATISFIABLE" outKisSAT
    egrep "decisions" outKisSAT
    show_elapsed_time
    echo "misat:"
    start_measuring_time
    ./misat < $f
    stop_measuring_time
    show_elapsed_time
done
