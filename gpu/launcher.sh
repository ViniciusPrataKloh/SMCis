#!/bin/bash

sleep 2 ;
PID=`ps a | grep ./gpu_monitoring_module.sh | awk '{print $1}'` ;
APP="" ;
BIN="" ;

echo "| App: " $APP ;
echo "" ;

echo "Waiting..." ;
sleep 30 ;
echo "Running the application..." ;
$BIN ;
echo "Waiting..." ;
sleep 30 ;

kill $PID ;
