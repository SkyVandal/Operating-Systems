#!/bin/bash
#chmod +x doTest.sh

num_threads=$1
file=$2
speed_up_file=${file}.speedups.csv
resfile=${file}.res

./SeqSolver/CircuitRouter-SeqSolver $file

for ((count=1; count<=$num_threads; count++));
do
    if [ $count = 1 ]; then
        if [ -f "$resfile" ]; then
            seq_solver_speed=$(cat $resfile | grep time | cut -d " " -f7)
            echo 1S,$seq_solver_speed,1 > $speed_up_file
        fi
    fi
    ./ParSolver/CircuitRouter-ParSolver -t $count $file

    par_solver_speed=$(cat $resfile | grep time | cut -d " " -f7)
    speedup=$(echo "scale=6; ${seq_solver_speed}/${par_solver_speed}" | bc)
    echo $count,$par_solver_speed,${speedup} >> $speed_up_file

done
