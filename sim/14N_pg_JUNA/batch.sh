#!/usr/bin/bash

nohup ./auto.sh 7556 &
echo $!
wait

nohup ./auto.sh 6859 &
echo $!
wait

nohup ./auto.sh 6792 &
echo $!
wait

nohup ./auto.sh 6172 &
echo $!
wait

nohup ./auto.sh 5240 &
echo $!
wait

nohup ./auto.sh 5180 &
echo $!
wait