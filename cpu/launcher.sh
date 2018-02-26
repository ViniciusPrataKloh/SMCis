#!/bin/bash

APP="lud_omp" ;
NUM_THREADS="12" ;
export OMP_NUM_THREADS=$NUM_THREADS ;
DIR_OUTPUT="/home/viniciuspk/Documents/Experiments/Monitors/results_omp/teste" ;
BIN="/home/viniciuspk/Documents/Experiments/rodinia_3.1/openmp/lud/omp/lud_omp -i /home/viniciuspk/Documents/Experiments/rodinia_3.1/data/lud/16384.dat" ;

i=1 ;
NUMBER_EXECS=1 ;

echo "| App: " $APP ;
echo "| Threads:" $NUM_THREADS ;

timestamp() {
        date +"%Y-%m-%d	%H:%M:%S.%2N" >> $DIR_OUTPUT/$APP-start_end.dat ;
}

while [ $i -le $NUMBER_EXECS ] ; do
	echo "Waiting..." ;
	sleep 30s ;
	echo "Running application..." ;
	timestamp ;
	$BIN ;
	timestamp ;
	echo "Waiting..." ;
	sleep 30s ;
	i=$((i+1)) ;
done ;
