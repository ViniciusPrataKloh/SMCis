#!/bin/bash

sleep 2 ;
PID=`ps a | grep ./gpu_monitoring_module.sh | awk '{print $1}'` ;
BIN=""

sleep 30 ;
$BIN ;
sleep 30 ;

kill $PID ;
