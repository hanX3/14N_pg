#!/usr/bin/bash

for (( i=20; i<=300; i+=20 )); 
do
  nohup ./auto.sh ${i} &
  echo $!
  wait
done