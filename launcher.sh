#!/bin/bash

PID=`ps a | grep GPU_module_monitor.sh | awk '{print $1}'` ;

sleep 30 ;
./lud_cuda -i ../../../data/lud/16384.dat ;
sleep 30 ;

kill $PID ;
