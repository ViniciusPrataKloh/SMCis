#!/bin/bash

APP="" ;
NUM_THREADS="" ;
export OMP_NUM_THREADS=$NUM_THREADS ;
BIN="" ;

i=1 ;
NUMBER_EXECS=1 ;

echo "| App: " $APP ;
echo "| Threads:" $NUM_THREADS ;
echo "" ;

timestamp() {
        date +"%Y-%m-%d	%H:%M:%S.%2N" >> start_end.dat ;
}

while [ $i -le $NUMBER_EXECS ] ; do
	echo "Waiting..." ;
	sleep 30s ;
	echo "Running the application..." ;
	timestamp ;
	$BIN ;
	timestamp ;
	echo "Waiting..." ;
	sleep 30s ;
	i=$((i+1)) ;
done ;
