#!/bin/bash

while true
do
	date +%H:%M:%S.%N | \
            awk '{print "time \t"$1}'
	sudo ipmitool dcmi power reading | \
	    grep Instantaneous | \
	    awk '{print $2"("$5")\t"$4}'

 	sudo ipmitool sdr type Temperature | \
 	    grep -i PU | \
 	    grep -i temp | \
 	    awk '{print $1,$2"\t"$10}'

        ./GPU_monitor
#	sleep 1
done
