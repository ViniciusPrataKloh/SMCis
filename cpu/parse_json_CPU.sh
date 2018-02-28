#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Necessário informar os arquivos com os resultados como parâmetro, na seguinte ordem:" ;
        echo "./parse_json_CPU.sh <nome da aplicação.dat> <power.dat> <temperature.dat>" ;
	echo "" ;
	exit 1 ;
fi

echo "Parsing the results to the json format." ;
echo "" ;

FILE_1=$1 ;
FILE_2=$2 ;
FILE_3=$3 ;

START_TIME=`head -n 1 $FILE_1 | awk '{print $2}'` ;

TIME=0 ;
CPU=0 ;
MEM=0 ;
POWER=0 ;
TEMP=0 ;

i=1 ;
LINES=`wc -l $FILE_1 | awk '{print $1}'` ;
echo "[" >> parsed.json ;

while [ $i -le $LINES ]; do

	TIME=`cat $FILE_1 | head -n $i | tail -n 1 | awk '{print $1}'` ;
	COUNTING_TIME=`expr $TIME - $START_TIME` ;

	CPU=`cat $FILE_1 | head -n $i | tail -n 1 | awk '{print $3}'` ;
	CPU=$(echo $CPU | sed 's/\(,\)/./g') ;
	MEM=`cat $FILE_1 | head -n $i | tail -n 1 | awk '{print $4}'` ;
	MEM=$(echo $MEM | sed 's/\(,\)/./g') ;
	POWER=`cat $FILE_2 | head -n $i | tail -n 1` ;
	TEMP_CPU1=`cat $FILE_3 | head -n $i | tail -n 1 | awk '{print $1}'` ;
	TEMP_CPU2=`cat $FILE_3 | head -n $i | tail -n 1 | awk '{print $2}'` ;

	if [ $i -eq $LINES ]; then
		echo "	{\"time\": $COUNTING_TIME, \"cpu\": $CPU, \"memory\": $MEM, \"power\": $POWER, \"temperature_cpu_1\": $TEMP_CPU1, \"temperature_cpu_2\": $TEMP_CPU2}" >> parsed.json ;
		echo "]" >> parsed.json ;
	elif [ $i -ne $LINES ]; then
		echo "	{\"time\": $COUNTING_TIME, \"cpu\": $CPU, \"memory\": $MEM, \"power\": $POWER, \"temperature_cpu_1\": $TEMP_CPU1, \"temperature_cpu_2\": $TEMP_CPU2}," >> parsed.json ;
	fi;
	i=$((i+1)) ;
done ;

