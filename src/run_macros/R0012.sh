#!/usr/bin/bash

rm ../../../data/R0012/*.root

cd ../

./ana_batch 12 0 157937 &
./ana_batch 12 157937 315874 &
./ana_batch 12 315874 473811 &
./ana_batch 12 473811 631748 &
./ana_batch 12 631748 789685 &
./ana_batch 12 789685 947622 &
