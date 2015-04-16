#!/bin/sh

for count in `seq 10000`
do
#	touch $count.txt
#	dmesg > $count.txt
#	echo "/home/sulit/src/tmptest/$count.txt" >> test.txt
done

ls *.txt > out.txt
