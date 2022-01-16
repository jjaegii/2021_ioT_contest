#!/bin/bash
./lcd
while :
do
	while read MAC floor name;
	do
		if ( bluetoothctl connect $MAC | grep "successful" > /dev/null ); # 연결 성공
		then
			rssi=$(hcitool rssi $MAC | grep -o '[0-9]*')
			if [ $rssi -gt 0 ];
			then
				date
				echo "연결 성공! $floor층 $name 거주민 진입"
				./run $floor $name
			fi
			bluetoothctl disconnect > /dev/null
		else
			bluetoothctl disconnect > /dev/null
			date
			echo "근처에 거주민 없음"
		fi
	done < deviceMAC.txt
done

