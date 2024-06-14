# FILENAME: mkdirs
#! /bin/bash
if [ -z $1 ]
    	then echo "命令格式：$0 < subdirname >"
    	echo "例如：$0 ZSMPI"
    	exit
fi
for m in master slave1 slave2  
do
echo ”ssh $m mkdir $1”
ssh $m mkdir $1
done